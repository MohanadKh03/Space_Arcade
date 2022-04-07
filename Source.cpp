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
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
            RunMenuEvents(window, main, isMenuOpened, playPressed,event);

            if (Keyboard::isKeyPressed(Keyboard::R)) {
                game brickBreakerGame("2.Breakout C++ SFML", score_BrickBreaker);
                brickBreakerGame.run(score_BrickBreaker);
            }
        }
        window.clear();
        camera.setCenter(YP.getPosition());

        if (isMenuOpened) {
            window.draw(s_mainBG);
            main.draw(window);
        }
        if (playPressed) {
            window.setView(camera);
            window.draw(Bg1);
            MovementSpaceShip(window, camera, YP, x, y);
            window.draw(YP);
        }

        window.display();
    }

    return 0;
}