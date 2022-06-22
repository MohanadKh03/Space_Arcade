#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.h"
#include "SpaceShipEvents.h"
#include "Breaker.h"
#include "Duck.h"
#include "Invaders.h"
#include "FileStreams.h"
using namespace std;
using namespace sf;

int main()
{
    //RenderWindow window(VideoMode(1360,768), "Space Arcade");
    RenderWindow window(VideoMode::getFullscreenModes()[0], "Space Arcade", sf::Style::None);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    int windowX = (int)window.getSize().x;
    int windowY = (int)window.getSize().y;

    Clock gameClock;
    float dt = 0.0f;

    int gameID = 0; // At the beginning
                    // 0 - Main Menu and Spaceship
                    // 1 - Brick Breaker game
                    // 2 - Space Shooter game
                    // 3 - Space Invaders game
                    // 4 - Leaderboard
    int collisionID = 0;

    //booleans for the Menu itself and Play  
    Menu main(window, (float)windowX, (float)windowY);
    bool isMenuOpened = true, credits = false, UsernameTyping = false, isSpaceshipMap = false, GamePlayed = false;

    View camera(Vector2f(0.0f, 0.0f), Vector2f((float)window.getSize().x / 2, (float)window.getSize().y / 2));


    SpaceShip spaceShipStruct(window, gameID, dt, camera);

    //The 3 Games
    myPlayer user;
    game* brickBreakerGame = NULL;
    Duck* duck = NULL;
    SpaceInvader* sp = NULL;

    Music MainMenu;
    MainMenu.openFromFile("Sounds/Main/meet-the-princess.wav");
    MainMenu.play();
    Music MapMusic;
    MapMusic.openFromFile("Sounds/Main/MapMusic.wav");
    MapMusic.setLoop(true);
    MapMusic.pause();

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
            //Menu and Username Events
            if (gameID == 0) {
                //EVENTS OF THE USERNAME TYPING
                if (UsernameTyping) {
                    user.TypeUsername(event, isSpaceshipMap, UsernameTyping);
                    if (isSpaceshipMap && gameID == 0)
                        MapMusic.play();
                    else
                        MainMenu.stop();
                }

                RunMenuEvents(window, main, isMenuOpened, UsernameTyping, credits, event);
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter) && canPlay && collison && collisionID <= 4) {
                gameID = collisionID;
                canPlay = false;
                MapMusic.pause();
            }

            if (Keyboard::isKeyPressed(Keyboard::E))
                gameID = 0;

            if (isSpaceshipMap) {
                if (Keyboard::isKeyPressed(Keyboard::H)) {
                    window.setView(window.getDefaultView());
                    MapMusic.stop();
                    isSpaceshipMap = false;
                    isMenuOpened = true;
                    MainMenu.play();
                }
            }
            if (gameID == 1)
            {
                brickBreakerGame->event(window, event, gameID);
            }

        }


        window.clear();

        //NO game yet .. Only the beginning (Main and username) then the spaceship stuff
        if (gameID == 0) {
            main.draw(window, isMenuOpened); //Draw main menu

            //Let all games point at NULL to avoid dangling pointers
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
            
            if (MapMusic.getStatus() == Music::Status::Paused)
                MapMusic.play();

            //Update the spaceship designs and basically all the spaceship sprites,boxes, etc..
            if (isSpaceshipMap)
                spaceShipStruct.Update(window, camera, dt, collisionID);

            //Saving
            if (GamePlayed) {
                user.Save();
                GamePlayed = false;
            }

            camera.setCenter(spaceShipStruct.YourPlayer.getPosition());

            if (UsernameTyping)
            {
                //DO ALL THE USERNAME SHOWING THEN ENTERING STUFF
                Text ShowTheUser, Username;
                Font SHOW_USER_FONT, USER_FONT;
                SHOW_USER_FONT.loadFromFile("Fonts/ARCADE_R.ttf");
                USER_FONT.loadFromFile("Fonts/ARCADE_I.ttf");
                texts(ShowTheUser, "Enter your username", (float)window.getSize().x / 4.f, (float)window.getSize().y / 2.f, (int)((float)window.getSize().x / 35.0f), SHOW_USER_FONT);
                window.draw(ShowTheUser);
                texts(Username, user.playerName, ShowTheUser.getPosition().x + (ShowTheUser.getGlobalBounds().width / 3.5f), ShowTheUser.getPosition().y + 100, (int)((float)window.getSize().x / 45.0f), USER_FONT);
                window.draw(Username);
            }
            if (credits) {
                Text names[7], backspace;
                Font font; font.loadFromFile("Fonts/World-of-spell.ttf");
                getCreditsNames(window, names, backspace, font, credits, isMenuOpened);
            }


        }

        //Brick Breaker
        else if (gameID == 1) {
            //MapMusic.pause();
            // Open the first game
            if (!brickBreakerGame)
            {
                brickBreakerGame = new game(&window, user.score_BrickBreaker);
                GamePlayed = true;
            }
            window.setView(window.getDefaultView());
            brickBreakerGame->deltaTime = dt;
            brickBreakerGame->run(window, event, user.score_BrickBreaker, gameID, dt);
        }
        //Duck Shooter
        else if (gameID == 2) {
            //MapMusic.pause();
            if (!duck)
            {
                duck = new Duck(window);
                GamePlayed = true;
            }
            // Open the second game
            window.setView(window.getDefaultView());
            duck->Update(window, event, dt, gameID, user.scoreDuck);

        }
        //Space Invader
        else if (gameID == 3) {
            //MapMusic.pause();
            if (!sp)
            {
                sp = new SpaceInvader(window);
                GamePlayed = true;
            }
            window.setView(window.getDefaultView());
            sp->Run(window, user.score_SpaceInvader, event, dt, gameID);
        }
        //Leaderboard
        else if (gameID == 4) {
            //MapMusic.pause();
            window.setView(window.getDefaultView());
            myPlayer temporary[30];
            Load(window, temporary);
        }

        window.display();
        // Store the time elapsed is a single frame into a variable
        dt = gameClock.getElapsedTime().asSeconds();


    }
    return 0;
}