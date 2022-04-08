#include <fstream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "SpaceShipEvents.h"
#include "game.h"
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
    
    int score_BrickBreaker = 0;
    int x = 0, y = 0;
    // layers
    Texture GM;
    GM.loadFromFile("game machine.png");
    Sprite GM1(GM);
    const float GMscale = 0.15f;
    GM1.setScale(GMscale, GMscale);
    GM1.setPosition(30, 80);
    Texture botttomwall;
    botttomwall.loadFromFile("bottomwall.jpg");
    Sprite BW1(botttomwall);
    const float BW1scale = 0.799f;
    BW1.setScale(BW1scale, BW1scale);
    BW1.setPosition(1046, 599.5);
    Texture Bluescreen;
    Bluescreen.loadFromFile("Bluescreen.jpg");
    Sprite BS1(Bluescreen);
    const float BS1scale = 0.799f;
    BS1.setScale(BS1scale, BS1scale);
    BS1.setPosition(1100, 190);
    Texture wall;
    wall.loadFromFile("wall.jpg");
    Sprite wall1(wall);
    const float wallscale = 0.799f;
    wall1.setScale(wallscale, wallscale);
    wall1.setPosition(1040, 70);
    Texture wall2;
    wall2.loadFromFile("wall2.jpg");
    Sprite wall3(wall2);
    const float wall2scale = 0.799f;
    wall3.setScale(wall2scale, wall2scale);
    wall3.setPosition(1040, 520);
    Texture wall4;
    wall4.loadFromFile("wall3.jpg");
    Sprite wall5(wall4);
    const float wall3scale = 0.799f;
    wall5.setScale(wall3scale, wall3scale);
    wall5.setPosition(1040, 250);

    //end of layers
    Texture t;
    Texture Bg;
    Bg.loadFromFile("background2.jpg");
    Sprite Bg1(Bg);
    const float Bgscale = 0.8f;
    Bg1.setScale(Bgscale, Bgscale);
    Bg1.setPosition(0, 0);
    t.loadFromFile("yellow hair boy.png");
    Sprite YP;
    View camera(Vector2f(0.0f,0.0f), Vector2f((float)windowX / 2, (float)windowY / 2));
    YP.setTexture(t);
    YP.setTextureRect(IntRect(x * 64, 0 * 64, 64, 64));
    YP.setPosition(windowX / 2.f, windowY / 2.f);
    //ggggggggggg

    game brickBreakerGame(&window, score_BrickBreaker);

    while (window.isOpen())
    {
        gameClock.restart();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::R)) {
                gameID = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                gameID = 0;
            }

            brickBreakerGame.event(window, event);
        }

        window.clear();
        if (gameID == 0) {
            // Open the main menu and the space ship
            RunMenuEvents(window, main, isMenuOpened, playPressed, event);
            camera.setCenter(YP.getPosition());
            if (isMenuOpened) {
                window.draw(s_mainBG);
                main.draw(window);
            }
            if (playPressed) {
                window.setView(camera);
                window.draw(GM1);
                window.draw(wall5);
                window.draw(wall3);
                window.draw(wall1);
                window.draw(BS1);
                window.draw(Bg1);
                MovementSpaceShip(window, camera, YP, x, y, GM1, BS1, wall1, wall3, wall5);
                window.draw(YP);
                window.draw(BW1);
            }
        }
        else if (gameID == 1) {
            // Open the first game
            window.setView(window.getDefaultView());
            brickBreakerGame.deltaTime = dt;
            brickBreakerGame.run(window, event, score_BrickBreaker);
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