#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

//bool gameStart;
//bool gameOver = false;


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
	void Update(RenderWindow&, Event&, float&, int&, int&);
	void Render(RenderWindow&, int&);
	void SpawnShips(RenderWindow&);
	void playEffect(Vector2f position);
	Font font;
	Text text;
	Text score_text;
	
	

private:
	int texture_index = 0;
	int friend_index = 0;
	Ship enemies[20];
	int directionIndex = 0;
	int positionIndex = 0;
	float enemyDelay = 0;
	float delay = 0.1f;
	float shipSpeed = 200.0f;
	int enemiesCount = 0;
	Vector2f enemiesScale = { 1.8f,1.8f };
	int friendliesMaxCount = 4;
	int maxEnemies = 2;
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
	int health = 20;

	int level = 0;

	RectangleShape crosshair;
};