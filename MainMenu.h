#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

// Player data struct
struct myPlayer {
    string playerName;
    int score_BrickBreaker = 0;
    int scoreDuck = 0;
    int score_SpaceInvader = 0;
    int sum;

    void TypeUsername(Event&, bool&, bool&);
    void Save();
};

struct Menu {
    int SELECTEDIndex;
    Font font;
    Text menu[6];
    Texture t_mainBG;
    Sprite s_mainBG;
    int factor;
    Texture SpaceMan;
    Sprite Spacer;
    Clock RotationClock;


    //constructor of the Menu 
    Menu(RenderWindow& window, float width, float height);
    //Draw the text
    void draw(RenderWindow& window, bool& isMENU);
    //Moving Up and Down using arrows
    void MoveUp();
    void MoveDown();
    //

    //Return the index which is selected by moving the arrows
    int getPressed();
};
void texts(Text& x, string txt, float coordX, float coordY, int charSize, Font& font);
void RunMenuEvents(RenderWindow& window, Menu& main, bool& isMENU, bool& USERNAME, bool& credits, Event& event);