#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.h"
#include "SpaceShipEvents.h"
#include "Breaker.h"
#include "Duck.h"
#include "Invaders.h"
using namespace std;
using namespace sf;

struct myPlayer {
    string playerName;
    int score_BrickBreaker = 0;
    int scoreDuck = 0;
    int score_SpaceInvader = 0;
    int sum;
};

void TypeUsername(Event& event,bool& isSpaceshipMap,bool& UsernameTyping,myPlayer& user) {
    if (event.type == Event::TextEntered) {
        if (event.text.unicode != '\b') //just checking if the text is in unicode
            user.playerName += event.text.unicode;
    }
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::BackSpace) {
            if (!user.playerName.empty())
                user.playerName.pop_back(); //remove letters ONLY if the string isnt empty
        }

        if (event.key.code == Keyboard::Enter) {
            isSpaceshipMap = true;
            UsernameTyping = false;
        }
    }
}

void Save(myPlayer& mp) {
    ofstream file("Data/scoreboard.txt", ios::app);
    mp.sum = mp.score_BrickBreaker + mp.scoreDuck + mp.score_SpaceInvader;
    file << mp.playerName << " " << mp.score_BrickBreaker << " " << mp.scoreDuck << " " << mp.score_SpaceInvader << " " << mp.sum << endl;
    file.close();
}

bool compareAll(myPlayer& a, myPlayer& b) {
    return a.sum > b.sum;
}

void Load(RenderWindow& window, myPlayer mp[]) {
    ifstream file("Data/scoreboard.txt");
    int i = 0;
    while (file.good() && i != 30) {
        file >> mp[i].playerName >> mp[i].score_BrickBreaker >> mp[i].scoreDuck>> mp[i].score_SpaceInvader >> mp[i].sum;
        i++;
        file.clear();
    }
    file.close();

    for (int i = 0; i < 30; i++) {
        mp[i].sum = mp[i].score_BrickBreaker + mp[i].scoreDuck + mp[i].score_SpaceInvader;
    }

    sort(mp, mp + 30, compareAll);

    Text Name, Games[4];
    Text rankUser[5], rankBB[5], rankSS[5], rankSI[5], rankSUM[5];
    Font font;
    font.loadFromFile("Fonts/AmbersHand-Regular.ttf");

    texts(Name, "Name", 100, 100, 50, font);
    texts(Games[0], "BRICK BREAKER", 350, 100, 50, font);
    texts(Games[1], "SPACE SHOOTER", 750, 100, 50, font);
    texts(Games[2], "SPACE INVADER", 1150, 100, 50, font);
    texts(Games[3], "SUM", 1550, 100, 50, font);

    window.draw(Name);
    for (int i = 0; i < 4; i++) {
        window.draw(Games[i]);
    }


    int j = 0;
    while (j != 5) {
        texts(rankUser[j], mp[j].playerName, Name.getPosition().x, Name.getPosition().y + 120 + j * 50, 30, font);
        texts(rankBB[j], to_string(mp[j].score_BrickBreaker), Games[0].getPosition().x, Games[0].getPosition().y + 120 + j * 50, 25, font);
        texts(rankSS[j], to_string(mp[j].scoreDuck), Games[1].getPosition().x, Games[1].getPosition().y + 120 + j * 50, 25, font);
        texts(rankSI[j], to_string(mp[j].score_SpaceInvader), Games[2].getPosition().x, Games[2].getPosition().y + 120 + j * 50, 25, font);
        texts(rankSUM[j], to_string(mp[j].sum), Games[3].getPosition().x, Games[3].getPosition().y + 120 + j * 50, 25, font);


        window.draw(rankUser[j]);
        window.draw(rankBB[j]);
        window.draw(rankSS[j]);
        window.draw(rankSI[j]);
        window.draw(rankSUM[j]);
        j++;
    }
}

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

    int gameID = 0; // At the beginning
                    // 0 - Main Menu and Spaceship
                    // 1 - Brick Breaker game
                    // 2 - Space Shooter game
                    // 3 - Space Invaders game
                    // 4 - Leaderboard
    int collisionID = 0;

    //booleans for the Menu itself and Play  
    Menu main(window, (float)windowX, (float)windowY); 
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
                TypeUsername(event, isSpaceshipMap, UsernameTyping, user);
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
                    DuckGame.setVolume(4.0);
                    
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
                Save(user);
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
                texts(ShowTheUser, "Enter your username", window.getSize().x / 4.f, window.getSize().y / 2.f, 50, SHOW_USER_FONT);
                window.draw(ShowTheUser);
                texts(Username, user.playerName, ShowTheUser.getPosition().x+250, ShowTheUser.getPosition().y + 100, 35, USER_FONT);
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
        //2nd Game
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
        dt = gameClock.getElapsedTime().asSeconds();


    }
    return 0;
}