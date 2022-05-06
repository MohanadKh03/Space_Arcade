#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Ctime>
const int NumOfEnemies = 60;
const int NumOfBullets = 20;
const int NumOfEnemyBullets = 2;

struct powerups
{
	int effect;
	sf::CircleShape body;
	sf::Clock powerclock;
	sf::Time powerTime;
	bool powerSpared;
	bool powerConsumed;
	bool fireRate;
};
struct Bullet {
	sf::Vector2f speed = { 0,-900 };
	sf::RectangleShape body;
	bool released = false;
	void Update(float&);
};
struct Boss
{
	int health;
	sf::Sprite Boss;
	sf::Texture BossTexture;
	Bullet bossBullet;
};
struct Sheild
{
	sf::RectangleShape body;
	int health = 100;
	bool active;
};
struct InvaderEnemy
{
	float posx, posy, speedx = 120.f, speedy = 10.25f, health;
	int shootingchance;
	int transperancy = 0;
	int red = 255;
	int green = 255;
	int	blue = 255;
	sf::Texture enemytexture;
	Bullet enemybu;
	int bulletspeed;
	sf::Sprite enemy;
	int bulletIndex = 0;
	powerups enemypower;

};
struct Player {
	float posx, posy, speedx = 10.f;
	sf::Texture playertexture;
	sf::RectangleShape playersprite;
	bool Damaged;
	int health;
};

struct SpaceInvader {
	SpaceInvader(sf::RenderWindow& window);
	float WindowFactor = sf::VideoMode::getDesktopMode().width / sf::VideoMode::getDesktopMode().height;
	int score = 0;
	bool isgameover = false;
	sf::Clock karizmaBoss;
	sf::Time KarizmaTime;
	sf::Text GameOverText;
	sf::Font GameOverFont;
	sf::Text scoretext;
	sf::Font scorefont;
	sf::Text livestext;
	sf::Font livesfont;
	sf::Text SheildText[3];
	sf::Font SheildFont[3];
	InvaderEnemy enemies[NumOfEnemies];
	Player player;
	Bullet bullets[NumOfBullets];
	Sheild sheilds[3];
	Boss boss;
	int bulletIndex = 0;
	float bulletDelay = 0.0f;
	float bulletTimer = 0.1f;
	sf::Clock clock;
	sf::Time deltatimemove;
	void EnemyMovement(float dt, sf::Clock& clock, sf::Time& deltatimemove);
	void PlayerMovement();
	void Enemybulletfunction(float dt);
	void ShootBullet(float&);
	void bulletsFunction(sf::Event& event, float dt);
	void Collision(sf::RenderWindow& w, int& gameID);
	void GameOver(sf::RenderWindow& w, int& gameID);
	void Run(sf::RenderWindow&, int&, sf::Event&, float&, int& gameID);
	void Destroyandgen(float dt);
	void Boss();
	void Bossmovement(sf::Clock& karizmaBoss, sf::Time& karizmatime, float dt);
	void Sheild();
	void PowerUps(float dt);
};