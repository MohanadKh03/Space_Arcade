#include <fstream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "SpaceShipEvents.h"
#include "game.h"
#include "Duck.h"
#include "Invaders.h"
using namespace std;
using namespace sf;

struct myPlayer {
    string playerName;
    int score_BrickBreaker = 0;
    int score_2ndGame = 0;
    int score_SpaceInvader = 0;
};

void setTextureNSprite(Texture& te, Sprite& se,const float& scale,int xPos,int yPos) {
    se.setTexture(te);
    se.setScale(scale, scale);
    se.setPosition(xPos, yPos);
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

    float spriteDelay = 0.1f;
    float spriteTimer = 0.0f;

    //booleans for the Menu itself and Play  
    Menu main((float)windowX, (float)windowY); 
    bool isMenuOpened = true, UsernameTyping = false, isSpaceshipMap = false;

    //Main background
    Texture t_mainBG;
    t_mainBG.loadFromFile("BlackBG.jpg");
    Sprite s_mainBG(t_mainBG);
    s_mainBG.setScale(windowX / s_mainBG.getLocalBounds().width
                     ,windowY / s_mainBG.getLocalBounds().height);
    
    ///// LAYERS
    Texture GameMachine;
    GameMachine.loadFromFile("game machine.png");
    Sprite GM_Sprite;
    setTextureNSprite(GameMachine, GM_Sprite, 0.15f, 30, 80);

        Sprite GM_Sprite2;
        setTextureNSprite(GameMachine, GM_Sprite2, 0.18f, 1040, 80);
        GM_Sprite2.setScale(-0.18f, 0.18f);
        GM_Sprite2.setColor(Color::Red);

        Texture GameMachine3;
        GameMachine3.loadFromFile("SpaceInvaderMachineFinal.png");
        Sprite GM_Sprite3(GameMachine3);
        setTextureNSprite(GameMachine3, GM_Sprite3, 0.18f, 40, 500);
        
        Texture bottomwall;
        bottomwall.loadFromFile("bottomwall.jpg");
        Sprite BottomWall_Sprite;
        setTextureNSprite(bottomwall, BottomWall_Sprite, 0.799f, 1046, 599.5);

    Texture Bluescreen;
    Bluescreen.loadFromFile("Bluescreen.jpg");
    Sprite BS1;
    setTextureNSprite(Bluescreen, BS1, 0.799f, 1100, 190);

    Texture wall;
    wall.loadFromFile("wall.jpg");
    Sprite wall1;
    setTextureNSprite(wall, wall1, 0.799f, 1040, 70);

    Texture wall2;
    wall2.loadFromFile("wall2.jpg");
    Sprite wall3;
    setTextureNSprite(wall2, wall3, 0.799f, 1040, 520);

    Texture wall4;
    wall4.loadFromFile("wall3.jpg");
    Sprite wall5;
    setTextureNSprite(wall4, wall5, 0.799f, 1040, 250);
    //END OF LAYERS

    // Background's Stuff
        Texture Background;
        Background.loadFromFile("Background2 Final.jpg");
        Sprite Background_Sprite;
        setTextureNSprite(Background, Background_Sprite, 0.8f, 0, 0);

    //Player's Stuff
    Texture Player; 
    Player.loadFromFile("yellow hair boy.png");
    Sprite YourPlayer;
    setTextureNSprite(Player, YourPlayer,1, windowX / 2.f, windowY / 2.f);
    YourPlayer.setTextureRect(IntRect(0 * 64, 0 * 64, 64, 64));
    int x = 0, y = 0; // For the sprite sheet
    View camera(Vector2f(0.0f, 0.0f), Vector2f((float)windowX / 2, (float)windowY / 2)); 
    
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
            camera.setCenter(YourPlayer.getPosition());
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

            if (isSpaceshipMap) {
                window.draw(GM_Sprite);
                window.draw(wall5);
                window.draw(wall3);
                window.draw(wall1);
                window.draw(BS1);
                window.draw(Background_Sprite);
                window.draw(GM_Sprite2);
                window.draw(GM_Sprite3);
                window.setView(camera);
                window.draw(YourPlayer);
                Text test;
                MovementSpaceShip(window, camera, YourPlayer, x, y, GM_Sprite,GM_Sprite2, GM_Sprite3, BS1, wall1, wall3, wall5,gameID, dt, spriteTimer, spriteDelay);
                window.draw(BottomWall_Sprite);
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
    //cout << user.playerName << " : " << user.score_BrickBreaker << endl;
    return 0;
}