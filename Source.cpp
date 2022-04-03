#include <fstream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "SpaceShipEvents.h"
#include "game.h"
using namespace std;
using namespace sf;

int main()
{
    int screenWidth = 1600;
    int screenHeight = 900;
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Space Arcade");

    //booleans for the Menu itself and Play  
    Menu main(window.getSize().x, window.getSize().y); bool isMenuOpened = true, playPressed = false;

    //Main background
    Texture t_mainBG;
    t_mainBG.loadFromFile("BlackBG.jpg");
    Sprite s_mainBG(t_mainBG);
    s_mainBG.setScale(window.getSize().x / s_mainBG.getLocalBounds().width
                    , window.getSize().y / s_mainBG.getLocalBounds().height); //Scaling to the 
                                                                             //difference between
                                                                             //window AND photo
    //Space Background
    Texture t_spaceshipBG;
    t_spaceshipBG.loadFromFile("Spaceship.jfif");
    Sprite s_spaceshipBG(t_spaceshipBG);
    s_spaceshipBG.setScale(window.getSize().x / s_spaceshipBG.getLocalBounds().width
                           , window.getSize().y / s_spaceshipBG.getLocalBounds().height);
                                                                             //Scaling to the 
                                                                             //difference between
     //  gggggggggggggg
     // 
    int score = 0;

    int x = 0, y = 0;
    Texture t;
    Texture Bg;
    Bg.loadFromFile("background.jpg");
    Sprite Bg1(Bg);
    const float Bgscale = 0.8;
    Bg1.setScale(Bgscale, Bgscale);
    Bg1.setPosition(0, 0);
    t.loadFromFile("yellow hair boy.png");
    Sprite YP;
    View camera(sf::FloatRect(0, 0, 600, 600));
    
    YP.setTexture(t);
    YP.setTextureRect(IntRect(x * 64, 0 * 64, 64, 64));
    YP.setPosition(500, 500);                                                                        //window AND photo
    //ggggggggggg
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            RunMenuEvents(window, main, isMenuOpened, playPressed,event);
            if (playPressed)
                MovementSpaceShip(window, camera, YP, x, y);

            if (Keyboard::isKeyPressed(Keyboard::R)) {
                game brickBreakerGame("2.Breakout C++ SFML", score);
                brickBreakerGame.run(score);
            }
        }
        camera.setCenter(YP.getPosition());

        window.clear();
        if (isMenuOpened) {
            window.draw(s_mainBG);
            main.draw(window);
        }
        if (playPressed) {
            window.draw(s_spaceshipBG);
            window.draw(YP);
        }

        window.display();
    }

    return 0;
}