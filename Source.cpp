#include <fstream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "SpaceShipEvents.h"
#include "game.h"
#include "Duck.h"
#include "Invaders.h"
using namespace std;
using namespace sf;

int main()
{
    //RenderWindow window(VideoMode(1600,900), "Space Arcade");
    RenderWindow window(VideoMode::getFullscreenModes()[0], "Space Arcade", sf::Style::None);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    int windowX = (int)window.getSize().x;
    int windowY = (int)window.getSize().y;

    Clock gameClock;
    float dt = 0.0f;

    float spriteDelay = 0.09f;
    float spriteTimer = 0.0f;

    int gameID = 0; // At the beginning

    //booleans for the Menu itself and Play  
    Menu main((float)windowX, (float)windowY); 
    bool isMenuOpened = true, UsernameTyping = false, isSpaceshipMap = false;

    View camera(Vector2f(0.0f, 0.0f), Vector2f((float)window.getSize().x / 2, (float)window.getSize().y / 2));

    //Main background
    Texture t_mainBG;
    t_mainBG.loadFromFile("BlackBG.jpg");
    Sprite s_mainBG(t_mainBG);
    s_mainBG.setScale(window.getSize().x / s_mainBG.getLocalBounds().width
        , window.getSize().y / s_mainBG.getLocalBounds().height);

    bool spaceShip = false;
    SpaceShip spaceShipStruct(window, gameID, dt, camera, spaceShip);
    
    //The 3 Games
    myPlayer user;
    game* brickBreakerGame = new game(&window, user.score_BrickBreaker);
    Duck* duck = new Duck(window);
    SpaceInvader* sp = new SpaceInvader(window);


    //
    while (window.isOpen())
    {
        gameClock.restart();
        Event event;
        //Events
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            //EVENTS OF THE USERNAME TYPING
            if (UsernameTyping) {
                if (event.type == Event::TextEntered) {
                    if (isprint(event.text.unicode)) //just checking if the text is in unicode
                        user.playerName += event.text.unicode;
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::BackSpace) {
                        if (!user.playerName.empty())
                            user.playerName.pop_back(); //remove letters ONLY if the string isnt empty
                    }
                    if (event.key.code == Keyboard::Enter) {
                        //Save HERE THEN CHANGE THE FLOW FROM USERNAME TYPING TO MAP
                        UsernameTyping = false;
                        isSpaceshipMap = true;
                    }
                }
            }
            
            if (Keyboard::isKeyPressed(Keyboard::R)) {
                gameID = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                gameID = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                gameID = 2;
            }
            if (Keyboard::isKeyPressed(Keyboard::K)) {
                // Reset game when pressed again
                /*if(gameID!=3)
                    new (&sp) SpaceInvader(window);*/
                gameID = 3;
            }
            if(gameID == 1)
                brickBreakerGame->event(window, event);
        }

        window.clear();

        //NO game yet .. Only the beginning (Main and username) then the spaceship stuff
        if (gameID == 0) {
            // Open the main menu and the space ship
            RunMenuEvents(window, main, isMenuOpened,UsernameTyping, event);
            if (sp) {
                delete sp;
                sp = NULL;
            }
            if (brickBreakerGame) {
                delete brickBreakerGame;
                brickBreakerGame = NULL;
            }
            if (duck) {
                delete duck;
                duck = NULL;
            }

            if (isSpaceshipMap) {
                spaceShipStruct.MovementSpaceShip(window, camera, gameID, dt, spriteTimer, spriteDelay);
            }

            camera.setCenter(spaceShipStruct.YourPlayer.getPosition());
            if (isMenuOpened) {
                window.draw(s_mainBG);
                main.draw(window);
            }

            if (UsernameTyping)
            {
                //DO ALL THE USERNAME SHOWING THEN ENTERING STUFF
                Text ShowTheUser, Username;
                Font SHOW_USER_FONT, USER_FONT;
                SHOW_USER_FONT.loadFromFile("ARCADE_R.ttf");
                USER_FONT.loadFromFile("ARCADE_I.ttf");
                texts(ShowTheUser, "Enter your username", window.getSize().x / 4.f, window.getSize().y / 2.f, 50, SHOW_USER_FONT);
                window.draw(ShowTheUser);
                texts(Username, user.playerName, ShowTheUser.getPosition().x+250, ShowTheUser.getPosition().y + 100, 35, USER_FONT);
                window.draw(Username);
            }

        }
        //Brick Breaker
        else if (gameID == 1) {
            // Open the first game
            if(!brickBreakerGame)
                brickBreakerGame = new game(&window, user.score_BrickBreaker);

            window.setView(window.getDefaultView());
            brickBreakerGame->deltaTime = dt;
            brickBreakerGame->run(window, event, user.score_BrickBreaker,gameID);
        }
        //2nd Game
        else if (gameID == 2) {
            if(!duck)
                duck = new Duck(window);
            // Open the second game
            window.setView(window.getDefaultView());
            duck->Update(window, event, dt,gameID);
           
        }
        //Space Invader
        else if (gameID == 3) {
            if(!sp)
                sp = new SpaceInvader(window);
            window.setView(window.getDefaultView());
            sp->Run(window, user.score_SpaceInvader, event, dt,gameID);
        }


        
        window.display();
        dt = gameClock.getElapsedTime().asSeconds();
}
    return 0;
}