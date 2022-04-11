#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

using namespace std;
using namespace sf;

void texts(Text& x, string txt, float coordX, float coordY, int charSize, Font& font) {
    x.setString(txt);
    x.setPosition(Vector2f(coordX, coordY));
    x.setCharacterSize(charSize);
    x.setFont(font);
}


struct Menu {
    int SELECTEDIndex;
    Font font[2];
    Text menu[3];

    //constructor of the Menu 
    Menu(float width, float height) {
        if (!font[0].loadFromFile("ARCADE_N.ttf") || !font[1].loadFromFile("ARCADE_R.ttf")) {
            exit(1);
        }

        //Texts to be shown
        texts(menu[0], "Play", 100, height / 2, 35, font[0]);
        texts(menu[1], "Exit", 100, height / 1.5f, 35, font[0]);
        menu[0].setOutlineThickness(2.5);
        menu[1].setOutlineThickness(2.5);

        texts(menu[2], "Space Arcade", 300, height / 4, 65, font[1]);
        menu[2].setOutlineThickness(2); menu[2].setOutlineColor(Color::Black);
        menu[2].setFillColor(Color::Cyan);

        //First one is colored as if it's hovered 
        menu[0].setFillColor(Color::Cyan);
        SELECTEDIndex = 0;
    }
    //Draw the text
    void draw(RenderWindow& window) {
        for (int i = 0; i < 3; i++) {
            window.draw(menu[i]);
        }
    }
    //Moving Up and Down using arrows
    void MoveUp() {
        if (SELECTEDIndex == 1) {
            menu[SELECTEDIndex].setFillColor(Color::White);
            menu[SELECTEDIndex - 1].setFillColor(Color::Cyan);
            SELECTEDIndex--;
        }
    }
    void MoveDown() {
        if (SELECTEDIndex == 0) {
            menu[SELECTEDIndex].setFillColor(Color::White);
            menu[SELECTEDIndex + 1].setFillColor(Color::Cyan);
            SELECTEDIndex++;
        }
    }
    //

    //Return the index which is selected by moving the arrows
    int getPressed() {
        return SELECTEDIndex;
    }
};

void RunMenuEvents(RenderWindow& window, Menu& main, bool& isMENU,bool& USERNAME,Event& event) {
        //The start of the program , basically all the menu stuff .
        if (isMENU) {
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
                    isMENU = false;
                    USERNAME = true;
                    break;
                case 1:
                    window.close();
                    break;
                }
            }
        }
}

#endif