#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

struct Ship {
public:
	Ship();
	void Update(RenderWindow&, float&, int&, int&);
	void Death_Check(RenderWindow&);
	Vector2f position = { 0,0 };
	Vector2f speed = { 0,0 };
	bool alive = false;
	RectangleShape duck;
	Texture texture1;
	Texture texture2;
	Texture texture3;
	Texture texture4;
	Texture texture5;
	Texture texture6;
	Texture texture7;
	bool friendly = false;

private:
	bool check_in = false;

};

struct Duck {
public:
	Duck(RenderWindow&);
	void ChooseTexture(Ship, int);
	void Update(RenderWindow&, Event&, float&, int&);
	void Render(RenderWindow&, int&);
	void SpawnShips(RenderWindow&);
	void playEffect(Vector2f position);
	Font font;
	Text text;
	Text score_text;

private:
	int texture_index = 0;
	int friend_index = 0;
	Ship enemies[40];
	//Ship friendlies[20];
	int directionIndex = 0;
	int positionIndex = 0;
	float enemyDelay = 0;
	float delay = 0.1f;
	float shipSpeed = 200.0f;
	int enemiesCount = 0;
	int friendliesMaxCount = 4;
	int maxEnemies = 9;
	//int maxFriendlies = 3;
	bool pressed = false;
	Texture cross;
	Texture background;
	Sprite backgroundsp;

	// special effect variables /////////////////////////////////////////
	Texture hitEffectTex;
	int spriteIndex = 0;
	float effectTimer = 0;
	float effectDelay = 0.05f;
	Sprite hitEffect;

	int score = 0;
	int health = 40;

	RectangleShape crosshair;
};