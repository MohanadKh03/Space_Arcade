#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <cmath>
#define _USE_MATH_DEFINES


using namespace std;
using namespace sf;
#pragma once
struct game
{
public:
	game(string title, int& score);
	void event(Event e);
	void update(float dt, int& score);
	void render();
	void reset();
	void run(int& score);
	void playEffect(Vector2f position, float rotation);

private:
	// Window Variables
	RenderWindow window;
	Event e;

	bool paused = false;
	bool pressed = false;

	// Screen Dimensions
	float width;
	float height;

	// Ball & Player Variables
	CircleShape ball;
	RectangleShape paddle;
	float defaultspeed;
	float angle;
	Vector2f speed;

	// Blocks' Variables
	int blocksWidth = (int)width / 80;
	int blocksHeight = (int)height / 112;
	int blockWidth = 1;
	const int number = blocksWidth * blocksHeight;
	RectangleShape blocks[16][40];

	// UI Variables
	Font font;
	Text text, textLife;

	// GameManager Variables
	//int score = 0;
	float speedfactor;
	int lives = 1;
	bool flag = true;

	// special effect variables /////////////////////////////////////////
	Texture hitEffectTex;
	int spriteIndex = 0;
	float effectTimer = 0;
	float effectDelay = 0.05f;
	// special effects variables /////////////////////////////////////////
	Sprite hitEffect;

	int blockCount = 0;
};