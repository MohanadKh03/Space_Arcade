#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Ctime>
#include <SFML/Audio.hpp>
const int NumOfEnemies = 60;
const int NumOfBullets = 20;
const int NumOfEnemyBullets = 2;

using namespace sf;

//struct powerups
//{
//	int effect;
//	sf::CircleShape sprite;
//	sf::Clock powerclock;
//	sf::Time powerTime;
//	bool powerSpared;
//	bool powerConsumed;
//	bool fireRate;
//};


struct Bullet {
	// ------------------------------ DRAW variables
	RectangleShape sprite;

	// ------------------------------ FUNCTIONALITY variables
	Vector2f speed = { 0,-900 };
	bool released = false;

	// ------------------------------ FUNCTIONS
	void Update(float&);
};


struct Boss
{
	Texture *BossMissle;
	Sprite bossMissle;
	int health = 12;
	bool isBossActive = 0;
	bool isMovingright =true;
	bool isMovingleft = 0;
	bool wasMovingright = 0;
	bool wasMovingleft = 1;
	int bossGenCounter = 0;
	int bossCntCntPast = 0;
	sf::Sprite Boss;
	sf::Texture BossTexture;
	Bullet bossBullet;
};

// Defending shields variables
struct Sheild
{
	// ------------------------------ DRAW variables
	Texture texture;
	RectangleShape sprite;
	bool active = true;

	// ------------------------------ FUNCTIONALITY variables
	int health = 100;
};

// Enemies struct
struct Enemy
{
	// ------------------------------ MOVEMENT variables
	Vector2f pos = { 0.f,0.f };
	Vector2f speed = { 120.0f, 10.25f };
	int health = 0;

	// ------------------------------ DRAW variables
	Texture texture;
	Sprite sprite;
	int red = 255;
	int green = 255;
	int	blue = 255;
	// int alpha = 0;

	// ------------------------------ SHOOTING variables
	int shootingchance = 0;
	int bulletspeed = 0;
	int bulletIndex = 0;

	// ------------------------------ EXTRA variables
	Bullet bullet;
	SoundBuffer bulletBuffer;
	Sound bulletSound;
	//powerups enemypower;

};

// Player struct
struct Player {
	// ------------------------------ MOVEMENT variables
	Vector2f pos = { 0.f,0.f };
	float speedx = 10.f;

	// ------------------------------ DRAW variables
	Texture texture;
	SoundBuffer bulletBuffer;
	Sound bulletSound;
	RectangleShape sprite;
	bool Damaged = false;
	int health =5;
};

// Game Manager Struct
struct SpaceInvader {
	// ------------------------------ FONTS 
	Font GameOverFont;
	Font scorefont;
	Font livesfont;
	Font SheildFont[3];

	// ------------------------------ TEXTS
	Text GameOverText;
	Text scoretext;
	Text livestext;
	Text SheildText[3];

	// ------------------------------ Free INTS
	int score = 0;
	int animationTime = 0;

	// ------------------------------ TEXTURES
	Texture background;
	Texture laser;

	// ------------------------------ SPRITES
	Sprite bulletBuffer;
	Sprite backgroundsprite;

	// ------------------------------ GAME MANAGER Variables
	float WindowFactor = (float)(VideoMode::getDesktopMode().width / VideoMode::getDesktopMode().height);
	bool isgameover = false;
	bool ReleaseBoss;

	// ------------------------------ TIME Variables
	Clock karizmaBoss;
	Clock playerLaser;
	Time KarizmaTime;

	// ------------------------------ SOUND Variables
	Music backgroundMusic;

	// ------------------------------ Game Objects
	Enemy enemies[NumOfEnemies];
	Player player;
	Bullet bullets[NumOfBullets];
	Sheild sheilds[3];
	Boss boss;

	// ------------------------------ PLAYER BULLETS Variables
	int bulletIndex = 0;
	float bulletDelay = 0.0f;
	float bulletTimer = 0.1f;

	// ------------------------------ ENEMY useless Seif Variables
	Clock clock;
	Time deltatimemove;

	// ------------------------------ FUNCTIONS
	SpaceInvader(sf::RenderWindow& window);
	void EnemyMovement(float dt, Clock& clock, Time& deltatimemove);
	void PlayerMovement();
	/*void Enemybulletfunction(float dt);*/
	void ShootBullet(float&);
	void bulletsFunction(Event& event, float dt);
	void Collision(RenderWindow& w, int& gameID);
	void GameOver(RenderWindow& w, int& gameID);
	void Run(RenderWindow&, int&, Event&, float&, int& gameID);
	void Destroyandgen(float dt);
	void Boss();
	void audio();
	void Bossmovement(sf::Clock& karizmaBoss, sf::Time& karizmatime, float dt);
	void Sheild();
	/*void PowerUps(float dt);*/
};