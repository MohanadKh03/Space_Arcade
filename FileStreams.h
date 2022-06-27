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
    float windowY = (float)window.getSize().y;
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
    Texture screen;
    screen.loadFromFile("Textures/Main/LeaderBoard.png");
    Sprite LeaderScreen;
    LeaderScreen.setTexture(screen);
    LeaderScreen.setScale(2.35, 1.9);
    Text Name, Games[5];
    Text rankUser[8], rankBB[8], rankSS[8], rankSI[8], rankSUM[8];
    Text Instructions;
    Font Scorefont, LBfont;
    Scorefont.loadFromFile("Fonts/AndromedaSpace-Regular.ttf");
    LBfont.loadFromFile("Fonts/Planet 37.ttf");

    texts(Instructions, "Press 'E' to go back", windowX * 0.04f, windowY * 0.85f, (int)(windowX / 65), LBfont);
    Instructions.setFillColor(Color::Yellow);
    texts(Name, "Name", windowX * 0.08f, windowY * 0.12f, (int)(windowX / 55), LBfont);
    Name.setFillColor(Color::Yellow);
    texts(Games[0], "Brick Breaker", windowX * 0.2f, windowY * 0.12f, (int)(windowX / 55), LBfont);
    texts(Games[1], "Space Shooter", windowX * 0.4f, windowY * 0.12f, (int)(windowX / 55), LBfont);
    texts(Games[2], "Space Invader", windowX * 0.6f, windowY * 0.12f, (int)(windowX / 55), LBfont);
    texts(Games[3], "Total", windowX * 0.8f, windowY * 0.12f, (int)(windowX / 55), LBfont);
    texts(Games[4], "LEADERBOARD", windowX * 0.24f, windowY * 0, (int)(windowX / 25), LBfont);
    for (int i = 0; i < 5; i++)
    {
        Games[i].setFillColor(Color::Yellow);
    }
    Games[4].setScale(1.4f, 0.8f);
    window.draw(LeaderScreen);
    window.draw(Instructions);
    window.draw(Name);
    for (int i = 0; i < 5; i++)
        window.draw(Games[i]);


    int j = 0;
    while (j != 8) {
        texts(rankUser[j], mp[j].playerName, Name.getPosition().x - 40, Name.getPosition().y + 100 + j * 55, 40, Scorefont);
        texts(rankBB[j], to_string(mp[j].score_BrickBreaker), Games[0].getPosition().x + 50, Games[0].getPosition().y + 100 + j * 55, 35, Scorefont);
        texts(rankSS[j], to_string(mp[j].scoreDuck), Games[1].getPosition().x + 50, Games[1].getPosition().y + 100 + j * 55, 35, Scorefont);
        texts(rankSI[j], to_string(mp[j].score_SpaceInvader), Games[2].getPosition().x + 50, Games[2].getPosition().y + 100 + j * 55, 35, Scorefont);
        texts(rankSUM[j], to_string(mp[j].sum), Games[3].getPosition().x + 50, Games[3].getPosition().y + 100 + j * 55, 35, Scorefont);

        int rank = j;
        switch (rank) {
        case 0:
            rankUser[rank].setScale(1.3f, 1.3f);
            rankUser[rank].setFillColor(Color::Red);
            rankBB[rank].setScale(1.3f, 1.3f);
            rankBB[rank].setFillColor(Color::Red);
            rankSS[rank].setScale(1.3f, 1.3f);
            rankSS[rank].setFillColor(Color::Red);
            rankSI[rank].setScale(1.3f, 1.3f);
            rankSI[rank].setFillColor(Color::Red);
            rankSUM[rank].setScale(1.3f, 1.3f);
            rankSUM[rank].setFillColor(Color::Red);
            break;
        case 1:
            rankUser[rank].setScale(1.2f, 1.2f);
            rankUser[rank].setFillColor(Color::Red);
            rankBB[rank].setScale(1.2f, 1.2f);
            rankBB[rank].setFillColor(Color::Red);
            rankSS[rank].setScale(1.2f, 1.2f);
            rankSS[rank].setFillColor(Color::Red);
            rankSI[rank].setScale(1.2f, 1.2f);
            rankSI[rank].setFillColor(Color::Red);
            rankSUM[rank].setScale(1.2f, 1.2f);
            rankSUM[rank].setFillColor(Color::Red);
            break;
        case 2:
            rankUser[rank].setScale(1.1f, 1.1f);
            rankUser[rank].setFillColor(Color::Red);
            rankBB[rank].setScale(1.1f, 1.1f);
            rankBB[rank].setFillColor(Color::Red);
            rankSS[rank].setScale(1.1f, 1.1f);
            rankSS[rank].setFillColor(Color::Red);
            rankSI[rank].setScale(1.1f, 1.1f);
            rankSI[rank].setFillColor(Color::Red);
            rankSUM[rank].setScale(1.1f, 1.1f);
            rankSUM[rank].setFillColor(Color::Red);
            break;
        }

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
