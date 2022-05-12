#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;


void texts(Text& x, string txt, float coordX, float coordY, int charSize, Font& font) {
    x.setString(txt);
    x.setPosition(Vector2f(coordX, coordY));
    x.setCharacterSize(charSize);
    x.setFont(font);
}


void RunMenuEvents(RenderWindow& window, Menu& main, bool& isMENU, bool& USERNAME,bool& credits,bool& about, Event& event) {
    //The start of the program , basically all the menu stuff ..
    //main.draw(window, isMENU);
    if (isMENU) {
        switch (event.type) {
            //if the key is pressed then move up/down
        case Event::KeyReleased:
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
                isMENU = false;
                USERNAME = true;
                break;
            case 1:
                isMENU = false;
                about = true;
                break;
            case 2:
                isMENU = false;
                credits = true;
                break;
            case 3:
                window.close();
                break;
            }
        }
    }
}
//constructor of the Menu 
Menu::Menu(RenderWindow& window, float width, float height) {
    //Background
    t_mainBG.loadFromFile("Textures/Main/BlackBG.jpg");
    s_mainBG.setTexture(t_mainBG);
    s_mainBG.setScale(window.getSize().x / s_mainBG.getLocalBounds().width
        , window.getSize().y / s_mainBG.getLocalBounds().height);
    //SpacerMan
    float SpaceX = window.getSize().x * 0.75;
    float SpaceY = window.getSize().y * 0.5;
    SpaceMan.loadFromFile("Textures/Characters/Spacer.png");
    Spacer.setTexture(SpaceMan);
    Spacer.setScale((float)width/1000.0f, (float)width/1000.0f);
    Spacer.setPosition(SpaceX, SpaceY);
    factor = 1;

    font.loadFromFile("Fonts/Planet 37.ttf");
    //Texts to be shown
    texts(menu[0], "Play", width * 0.1f, height / 2.0f , width/50, font);
    texts(menu[1], "About", width * 0.1f, height / 1.75f, width / 50, font);
    texts(menu[2], "Credits", width * 0.1f, height / 1.5f, width/50, font);
    texts(menu[3], "Exit", width * 0.1f, height-200, width / 50, font);
    menu[0].setOutlineThickness(2.5);
    menu[1].setOutlineThickness(2.5);
    menu[2].setOutlineThickness(2.5);
    menu[3].setOutlineThickness(2.5);

    texts(menu[4], "Space Arcade", width/8.0f, height / 4, (int)(width/20), font);
    menu[4].setOutlineThickness(2); 
    menu[4].setOutlineColor(Color::Black);
    menu[4].setFillColor(Color::Cyan);

    //First one is colored as if it's hovered 
    menu[0].setFillColor(Color::Cyan);
    SELECTEDIndex = 0;
}
//Draw the text
void Menu::draw(RenderWindow& window, bool& isMENU) {
    if (isMENU) {
        window.draw(s_mainBG);
        for (int i = 0; i < 5; i++) {
            window.draw(menu[i]);
        }
        if (RotationClock.getElapsedTime().asSeconds() > 0.1) {
            factor += 1;
            RotationClock.restart();
        }

        Spacer.setRotation(1 + factor);
        window.draw(Spacer);
    }
}
//Moving Up and Down using arrows
void Menu::MoveUp() {
    if (SELECTEDIndex - 1 >= 0) {
        menu[SELECTEDIndex].setFillColor(Color::White);
        menu[SELECTEDIndex - 1].setFillColor(Color::Cyan);
        SELECTEDIndex--;
    }
}
void Menu::MoveDown() {
    if (SELECTEDIndex + 1  < 4) {
        menu[SELECTEDIndex].setFillColor(Color::White);
        menu[SELECTEDIndex + 1].setFillColor(Color::Cyan);
        SELECTEDIndex++;
    }
}
//

//Return the index which is selected by moving the arrows
int Menu::getPressed() {
    return SELECTEDIndex;
}