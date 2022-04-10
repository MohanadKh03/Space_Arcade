#include <fstream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "SpaceShipEvents.h"
#include "game.h"
using namespace std;
using namespace sf;

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

    int gameID = 0;

    //booleans for the Menu itself and Play  
    Menu main((float)windowX, (float)windowY); bool isMenuOpened = true, playPressed = false;

    //Main background
    Texture t_mainBG;
    t_mainBG.loadFromFile("BlackBG.jpg");
    Sprite s_mainBG(t_mainBG);
    s_mainBG.setScale(windowX / s_mainBG.getLocalBounds().width
                     ,windowY / s_mainBG.getLocalBounds().height); //Scaling to the 
                                                                             //difference between
                                                                             //window AND photo
    
    // LAYERS
        Texture GameMachine;
        GameMachine.loadFromFile("game machine.png");
        Sprite GM_Sprite;
        setTextureNSprite(GameMachine, GM_Sprite, 0.15f, 30, 80);

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

    // Background Stuff
        Texture Background;
        Background.loadFromFile("background2.jpg");
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
        int score_BrickBreaker = 0;
        game brickBreakerGame(&window, score_BrickBreaker);

    while (window.isOpen())
    {
        gameClock.restart();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::R)) {
                gameID = 1;
            }
            if(gameID == 1)
                brickBreakerGame.event(window, event);
        }

        window.clear();
        if (gameID == 0) {
            // Open the main menu and the space ship
            RunMenuEvents(window, main, isMenuOpened, playPressed, event);
            camera.setCenter(YourPlayer.getPosition());
            if (isMenuOpened) {
                window.draw(s_mainBG);
                main.draw(window);
            }
            if (playPressed) {
                window.draw(GM_Sprite);
                window.draw(wall5);
                window.draw(wall3);
                window.draw(wall1);
                window.draw(BS1);
                window.draw(Background_Sprite);
                window.setView(camera);
                window.draw(YourPlayer);
                
                
                MovementSpaceShip(window, camera, YourPlayer, x, y, GM_Sprite, BS1, wall1, wall3, wall5);
                window.draw(BottomWall_Sprite);
            }
        }
        else if (gameID == 1) {
            // Open the first game
            window.setView(window.getDefaultView());
            brickBreakerGame.deltaTime = dt;
            brickBreakerGame.run(window, event, score_BrickBreaker,gameID);
        }
        else if (gameID == 2) {
            // Open the second game
        }
        else if (gameID == 3) {
            // Open the third game
        }
        window.display();
        dt = gameClock.getElapsedTime().asSeconds();
    }

    return 0;
}