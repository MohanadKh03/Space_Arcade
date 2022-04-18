#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

struct Enemy {
public:
	Enemy();
	void Update(RenderWindow&, float&, int&, int&);
	void Death_Check(RenderWindow&);
	Vector2f position = { 0,0 };
	Vector2f speed = { 0,0 };
	bool alive = false;
	RectangleShape duck;
private:
	bool check_in = false;

};

struct Duck {
public:
	Duck(RenderWindow&);
	void Update(RenderWindow&, Event&, float&,int&);
	void Render(RenderWindow&,int&);
	void SpawnEnemy(RenderWindow&);
	sf::Font font;
	sf::Text text;
	sf::Text score_text;
	//sf::Text dead;
private:
	Enemy enemies[20];
	int directionIndex = 0;
	int positionIndex = 0;
	float enemyDelay = 0;
	float delay = 1.0f;
	float enemySpeed = 200.0f;
	int enemiesCount = 0;
	int maxEnemies = 10;
	bool pressed = false;

	int score = 0;
	int health = 20;

	RectangleShape crosshair;
};
