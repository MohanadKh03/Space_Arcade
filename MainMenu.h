#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

struct Menu {
    int SELECTEDIndex;
    Font font;
    Text menu[3];
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
void RunMenuEvents(RenderWindow& window, Menu& main, bool& isMENU, bool& USERNAME, Event& event);
