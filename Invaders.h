#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
const int NumOfEnemies = 60;
const int NumOfBullets = 20;

struct InvaderEnemy
{
	float posx = 0, posy = 0, speedx = 10.25f, speedy = 10.25f, health;
	sf::Texture enemytexture;
	sf::Sprite enemy;
	bool Damaged = false;
};
struct Player {
	float posx, posy, speedx = 10.f;
	sf::Texture playertexture;
	sf::RectangleShape playersprite;
	bool Damaged;
	int health;
};
struct Bullet {
	sf::Vector2f speed = {0,-900};
	sf::RectangleShape body;
	bool released = false;
	void Update(float&);
};
struct SpaceInvader {
	float WindowFactor = (float)(sf::VideoMode::getDesktopMode().width / sf::VideoMode::getDesktopMode().height);
	int score = 0;

	sf::Text scoretext;
	sf::Font font;
	InvaderEnemy enemies[NumOfEnemies];
	Player player;
	Bullet bullets[NumOfBullets];
	int bulletIndex = 0;
	float bulletDelay = 0.0f;
	float bulletTimer = 0.1f;
	SpaceInvader(sf::RenderWindow& window);
	void EnemyMovement();
	void PlayerMovement();
	void ShootBullet(float&);
	void bulletsFunction(sf::Event& event, float dt);
	void Collision(sf::RenderWindow& w,int& gameID);

	void Run(sf::RenderWindow&, int&, sf::Event&, float&,int& gameID);
};