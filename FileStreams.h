#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.h"

using namespace std;

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
    float windowX = (float)window.getSize().x;
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

    texts(Name, "Name", windowX * 0.1f, 100, (int)(windowX / 40), font);
    texts(Games[0], "BRICK BREAKER", windowX * 0.2f, 100, (int)(windowX / 40), font);
    texts(Games[1], "SPACE SHOOTER", windowX * 0.4f, 100, (int)(windowX / 40), font);
    texts(Games[2], "SPACE INVADER", windowX * 0.6f, 100, (int)(windowX / 40), font);
    texts(Games[3], "SUM", windowX * 0.8f, 100, (int)(windowX / 50), font);

    window.draw(Name);
    for (int i = 0; i < 4; i++)
        window.draw(Games[i]);


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

void getCreditsNames(RenderWindow& window, Text txt[], Text& Backspace, Font& f, bool& credits, bool& isMenu) {
    Texture t_mainBG;
    Sprite s_mainBG;
    float windowX = (float)window.getSize().x;
    float windowY = (float)window.getSize().y;
    t_mainBG.loadFromFile("Textures/Main/BlackBG.jpg");
    s_mainBG.setTexture(t_mainBG);
    s_mainBG.setScale(windowX / s_mainBG.getLocalBounds().width
        , windowY / s_mainBG.getLocalBounds().height);

    texts(Backspace, "Press (Space) to go back!", windowX / 2.f, 50, 70, f);

    texts(txt[0], "Mo'men Kadry", windowX / 3.f, windowY - 800, 50, f);
    texts(txt[1], "Seif Sherif", windowX / 6.0f, windowY - 700, 50, f);
    texts(txt[2], "Youssef Ahmed", windowX / 3.0f, windowY - 600, 50, f);
    texts(txt[3], "Marwan Hossam", windowX / 6.0f, windowY - 500, 50, f);
    texts(txt[4], "Noureldin Hesham", windowX / 3.f, windowY - 400, 50, f);
    texts(txt[5], "Mohamed Barghush", windowX / 6.0f, windowY - 300, 50, f);
    texts(txt[6], "Mohanad Khaled", windowX / 3.f, windowY - 200, 50, f);

    window.draw(s_mainBG);
    window.draw(Backspace);
    for (int i = 0; i < 7; i++) {
        txt[i].setFillColor(Color::Cyan);
        window.draw(txt[i]);
    }
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        credits = false;
        isMenu = true;
    }
}
