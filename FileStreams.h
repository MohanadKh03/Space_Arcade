//#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.h"

using namespace std;

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

// User defined functions /////////////////////////////////////

void myPlayer::TypeUsername(Event& event, bool& isSpaceshipMap, bool& UsernameTyping) {
    if (event.type == Event::TextEntered) {
        if (event.text.unicode != '\b') //just checking if the text is in unicode
            playerName += event.text.unicode;
    }
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::BackSpace) {
            if (!playerName.empty())
                playerName.pop_back(); //remove letters ONLY if the string isnt empty
        }

        if (event.key.code == Keyboard::Enter) {
            isSpaceshipMap = true;
            UsernameTyping = false;
        }
    }
}

void myPlayer::Save() {
    ofstream file("Data/scoreboard.txt", ios::app);
    sum = score_BrickBreaker + scoreDuck + score_SpaceInvader;
    file << playerName << " " << score_BrickBreaker << " " << scoreDuck << " " << score_SpaceInvader << " " << sum << endl;
    file.close();
}

bool compareAll(myPlayer& a, myPlayer& b) {
    return a.sum > b.sum;
}

void Load(RenderWindow& window, myPlayer mp[]) {
    ifstream file("Data/scoreboard.txt");
    int i = 0;
    while (file.good() && i != 30) {
        file >> mp[i].playerName >> mp[i].score_BrickBreaker >> mp[i].scoreDuck >> mp[i].score_SpaceInvader >> mp[i].sum;
        i++;
        file.clear();
    }
    file.close();

    for (int i = 0; i < 30; i++) {
        mp[i].sum = mp[i].score_BrickBreaker + mp[i].scoreDuck + mp[i].score_SpaceInvader;
    }

    sort(mp, mp + 30, compareAll);

    Text Name, Games[4];
    Text rankUser[5], rankBB[5], rankSS[5], rankSI[5], rankSUM[5];
    Font font;
    font.loadFromFile("Fonts/AmbersHand-Regular.ttf");

    texts(Name, "Name", window.getSize().x * 0.1f, 100, window.getSize().x / 40, font);
    texts(Games[0], "BRICK BREAKER", window.getSize().x * 0.2f, 100, window.getSize().x / 40, font);
    texts(Games[1], "SPACE SHOOTER", window.getSize().x * 0.4f, 100, window.getSize().x / 40, font);
    texts(Games[2], "SPACE INVADER", window.getSize().x * 0.6f, 100, window.getSize().x / 40, font);
    texts(Games[3], "SUM", window.getSize().x * 0.8f, 100, window.getSize().x / 50, font);

    window.draw(Name);
    for (int i = 0; i < 4; i++) {
        window.draw(Games[i]);
    }


    int j = 0;
    while (j != 5) {
        texts(rankUser[j], mp[j].playerName, Name.getPosition().x, Name.getPosition().y + 120 + j * 50, 30, font);
        texts(rankBB[j], to_string(mp[j].score_BrickBreaker), Games[0].getPosition().x, Games[0].getPosition().y + 120 + j * 50, 25, font);
        texts(rankSS[j], to_string(mp[j].scoreDuck), Games[1].getPosition().x, Games[1].getPosition().y + 120 + j * 50, 25, font);
        texts(rankSI[j], to_string(mp[j].score_SpaceInvader), Games[2].getPosition().x, Games[2].getPosition().y + 120 + j * 50, 25, font);
        texts(rankSUM[j], to_string(mp[j].sum), Games[3].getPosition().x, Games[3].getPosition().y + 120 + j * 50, 25, font);


        window.draw(rankUser[j]);
        window.draw(rankBB[j]);
        window.draw(rankSS[j]);
        window.draw(rankSI[j]);
        window.draw(rankSUM[j]);
        j++;
    }
}
