#include <iostream>
#include <SFML/Graphics.hpp>
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
	game(RenderWindow* window, int& score);
	void event(RenderWindow& window, Event& e);
	void update(RenderWindow* window, int& score, int& gameNUMBER);
	void render(RenderWindow& window);
	void reset();
	void run(RenderWindow& window, Event& e, int& score, int& gameNUMBER);
	void playEffect(Vector2f position, float rotation);

	float deltaTime = 0.0f;

private:
	// Paused Variables
	bool paused = false;
	bool pressed = false;

	// Ball & Player Variables
	CircleShape ball;
	RectangleShape paddle;
	float defaultspeed;
	float angle;
	Vector2f speed;
	float lastPosition;
	float currentPosition;
	int direction = 0;
	int moveCheck = 0;

	// Ball Trail Variables
	CircleShape ballTrail[20];

	// Blocks' Variables
	int blocksWidth = 0;
	int blocksHeight = 0;
	int blockWidth = 1;
	const int number = blocksWidth * blocksHeight;
	RectangleShape blocks[16][40];

	// UI Variables
	Font font;
	Text text, textLife;

	// GameManager Variables
	float speedfactor;
	int lives = 1;
	bool flag = true;

	// special effect variables /////////////////////////////////////////
	Texture hitEffectTex;
	int spriteIndex = 0;
	float effectTimer = 0;
	float effectDelay = 0.05f;
	Sprite hitEffect;

	// Music and Sound effects variables
	SoundBuffer bgBuffer;
	Sound bgMusic;
	SoundBuffer effectBuffer;
	Sound effectSound;
	SoundBuffer loseBuffer;
	Sound loseSound;

	// For WIN condition
	int blockCount = 0;
};