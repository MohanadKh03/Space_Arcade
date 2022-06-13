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
    Menu main(window, windowX, windowY); 
    bool isMenuOpened = true, UsernameTyping = false, isSpaceshipMap = false, GamePlayed = false;

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
    Music DuckGame;
    DuckGame.openFromFile("Sounds/Duck/127706__cydon__spacebattle-with-laserwaepons001.wav");
    Music MapMusic;
    MapMusic.openFromFile("Sounds/Main/MapMusic.wav");
    MapMusic.setLoop(true);
    
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
                user.TypeUsername(event, isSpaceshipMap, UsernameTyping);
                if (isSpaceshipMap/* && !isMenuOpened && !UsernameTyping*/ && gameID == 0) {
                    MapMusic.play();
                }
                else
                    MainMenu.stop();
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter) && canPlay && collison) {
                gameID = collisionID;
                canPlay = false;
                if (gameID == 2)
                {   
                    MapMusic.pause();
                    DuckGame.play();
                    DuckGame.setLoop(true);
                    DuckGame.setVolume(30.0);
                    
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::E)) {
                gameID = 0;
               
            }

            if (gameID == 1)
            {
                MapMusic.pause();
                brickBreakerGame->event(window, event);
            }
            
        }


        window.clear();

        //NO game yet .. Only the beginning (Main and username) then the spaceship stuff
        if (gameID == 0) {
            
            // Open the main menu and the space ship
            RunMenuEvents(window, main, isMenuOpened,UsernameTyping, event);
            if (sp) {
                delete sp;
                sp = NULL;
                if (isSpaceshipMap) 
                    MapMusic.play();
                
            }
            if (brickBreakerGame) {
                delete brickBreakerGame;
                brickBreakerGame = NULL;
                if(isSpaceshipMap)
                   MapMusic.play();
            }
            if (duck) {
                delete duck;
                duck = NULL;
                DuckGame.stop();
                if(isSpaceshipMap)
                    MapMusic.play();
            }

            if (isSpaceshipMap) {
                spaceShipStruct.Update(window, camera, dt, collisionID);
            }
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
                texts(ShowTheUser, "Enter your username", window.getSize().x / 4.f, window.getSize().y / 2.f, window.getSize().x / 35.0f, SHOW_USER_FONT);
                window.draw(ShowTheUser);
                texts(Username, user.playerName, ShowTheUser.getPosition().x+(ShowTheUser.getGlobalBounds().width/3.5f), ShowTheUser.getPosition().y + 100, window.getSize().x / 45.0f, USER_FONT);
                window.draw(Username);
            }

        }
        
        //Brick Breaker
        else if (gameID == 1) {
            // Open the first game
            if (!brickBreakerGame)
            {
                brickBreakerGame = new game(&window, user.score_BrickBreaker);
                GamePlayed = true;
            }
            window.setView(window.getDefaultView());
            brickBreakerGame->deltaTime = dt;
            brickBreakerGame->run(window, event, user.score_BrickBreaker,gameID);
        }
        //Duck Shooter
        else if (gameID == 2) {
            
            if (!duck)
            {
                duck = new Duck(window);
                GamePlayed = true;
            }
                // Open the second game
            window.setView(window.getDefaultView());
            duck->Update(window, event, dt,gameID, user.scoreDuck);
        
        }
        //Space Invader
        else if (gameID == 3) {
            MapMusic.pause();
            if (!sp)
            {
                sp = new SpaceInvader(window);
                GamePlayed = true;
            }
            window.setView(window.getDefaultView());
            sp->Run(window, user.score_SpaceInvader, event, dt,gameID);
        }
        //Leaderboard
        else if (gameID == 4) {
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