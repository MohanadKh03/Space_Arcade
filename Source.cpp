#include <SFML/Graphics.hpp>
#include <fstream>
#include "MainMenu.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1200, 800), "Space Arcade");

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
                                                                             //window AND photo

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            //The start of the program , basically all the menu stuff .
            if (isMenuOpened) {
                switch (event.type) {
                    //if the key is pressed then move up/down
                    case Event::KeyPressed:
                        switch (event.key.code) {
                            case Keyboard::Up:
                                main.MoveUp();
                                break;
                            case Keyboard::Down:
                                main.MoveDown();
                                break;
                        }
                }
                //conditions when entered .. ez 
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    switch (main.getPressed()) {
                        case 0:
                            isMenuOpened = false;
                            playPressed = true;
                            break;
                        case 1:
                            window.close();
                            break;
                    }
                }
            }

        }

        window.clear();
        if (isMenuOpened) {
            window.draw(s_mainBG);
            main.draw(window);
        }
        if (playPressed)
            window.draw(s_spaceshipBG);

        window.display();
    }

    return 0;
}