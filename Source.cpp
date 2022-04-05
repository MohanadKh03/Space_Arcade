#include <fstream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "SpaceShipEvents.h"
#include "game.h"
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1600,900), "Space Arcade");

    //booleans for the Menu itself and Play  
    Menu main(window.getSize().x, window.getSize().y); bool isMenuOpened = true, playPressed = false;

    //Main background
    Texture t_mainBG;
    t_mainBG.loadFromFile("BlackBG.jpg");
    Sprite s_mainBG(t_mainBG);
    s_mainBG.setScale(window.getSize().x / s_mainBG.getLocalBounds().width
                     ,window.getSize().y / s_mainBG.getLocalBounds().height); //Scaling to the 
                                                                             //difference between
                                                                             //window AND photo
    
    int score_BrickBreaker = 0;
    // gg
    Texture GM;
    GM.loadFromFile("game machine.png");
    Sprite GM1(GM);
    const float GMscale = 0.15;
    GM1.setScale(GMscale, GMscale);
    GM1.setPosition(-480, -250);
    Texture box4;
    box4.loadFromFile("box3.png");
    Sprite box5(box4);
    const float box4scale = 1.2;
    box5.setScale(box4scale, box4scale);
    box5.setPosition(-360, 80);
    Texture box2;
    box2.loadFromFile("box3.png");
    Sprite box3(box2);
    const float box2scale = 1.2;
    box3.setScale(box2scale, box2scale);
    box3.setPosition(-296, 40);
    Texture box;
    box.loadFromFile("boxs2.png");
    Sprite box1(box);
    const float boxscale = 1.2;
    box1.setScale(boxscale, boxscale);
    box1.setPosition(-215, 58);
    Texture box6;
    box6.loadFromFile("boxs2.png");
    Sprite box7(box6);
    const float box6scale = 1.2;
    box7.setScale(box6scale, box6scale);
    box7.setPosition(-356, -38);
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
    View camera(Vector2f(0.f, 0.f), Vector2f(window.getSize().x,window.getSize().y));
    YP.setTexture(t);
    YP.setTextureRect(IntRect(x * 64, 0 * 64, 64, 64));
    YP.setPosition(window.getSize().x/ 2.f, window.getSize().y / 2.f);
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
                game brickBreakerGame("2.Breakout C++ SFML", score_BrickBreaker);
                brickBreakerGame.run(score_BrickBreaker);
            }
        }
        camera.setCenter(YP.getPosition());

        window.clear();
        if (isMenuOpened) {
            window.draw(s_mainBG);
            main.draw(window);
        }
        if (playPressed) {
            window.setView(camera);
            window.draw(GM1);
            window.draw(box7);
            window.draw(box5);
            window.draw(box3);
            window.draw(box1);
            window.draw(Bg1);
            window.draw(YP);
        }

        window.display();
    }

    return 0;
}