#include <SFML/Graphics.hpp>
#include <iostream>
#include "Invaders.h"
using namespace std;

bool movingright = true;
bool movingleft = false;
int side = sf::VideoMode::getDesktopMode().width - 20;
//bool released[NumOfBullets];
int z = 0;

SpaceInvader::SpaceInvader(sf::RenderWindow& window) {
	//show the score
	scoretext.setPosition(sf::Vector2f(window.getSize().x - 300, 0));
	scoretext.setString("Score: " + to_string(score));
	font.loadFromFile("ARCADE_R.ttf");
	scoretext.setFont(font);

	//Enemy Stuff
	enemies[0].posx = 20;
	enemies[0].posy = 0;
	enemies[0].enemytexture.loadFromFile("enemyBlack.png");
	enemies[0].enemy.setTexture(enemies[0].enemytexture);
	enemies[0].enemy.setScale(sf::Vector2f(0.75f, 0.75f));
	enemies[0].enemy.setPosition(sf::Vector2f(enemies[0].posx, enemies[0].posy));
	for (int i = 1; i < NumOfEnemies; i++)
	{

		enemies[i].enemytexture.loadFromFile("enemyBlack.png");
		enemies[i].enemy.setTexture(enemies[i].enemytexture);
		enemies[i].enemy.setScale(sf::Vector2f(0.75 * WindowFactor, 0.75 * WindowFactor));

		if (i == 0 || i % 10 != 0)
		{
			enemies[i].posx = enemies[i - 1].posx + 90 * WindowFactor;
			enemies[i].posy = enemies[i - 1].posy;
		}
		else if (i % 10 == 0)
		{
			enemies[i].posx = enemies[0].posx;
			enemies[i].posy = enemies[i - 1].posy + 90 * WindowFactor;
		}

		enemies[i].enemy.setPosition(sf::Vector2f(enemies[i].posx, enemies[i].posy));
	}
	//Player Stuff
	player.posx = sf::VideoMode::getDesktopMode().width / 2;
	player.posy = sf::VideoMode::getDesktopMode().height - 100;
	player.playertexture.loadFromFile("blueship.png");
	player.playersprite.setTexture(&player.playertexture);
	player.playersprite.setSize(sf::Vector2f(window.getSize().x / 21.68f, window.getSize().y / 14));
	//player.playersprite.setScale(sf::Vector2f(1.f, 1.f));
	player.playersprite.setPosition(sf::Vector2f(player.posx, player.posy));
	//Bullets stuff
	for (int i = 0; i < NumOfBullets; i++)
	{
		bullets[i].released = false;
		bullets[i].body.setSize(sf::Vector2f(2, 4));
		bullets[i].body.setPosition(player.posx, player.posy);
		//bullets[i].rect = bullets[i].body.getGlobalBounds();
	}
	// Reset the score
	score = 0;
}

void SpaceInvader::EnemyMovement() {
	//setting the x,y positions for the *already* set in the constructor ones
	for (int i = 0; i < NumOfEnemies; i++)
	{
		enemies[i].posx = enemies[i].enemy.getPosition().x;
		enemies[i].posy = enemies[i].enemy.getPosition().y;

	}
	//containing the enemies and moving them right/left and down if they reach the far end(right/left)
	//the down statement with right and left booleans
	if (enemies[0].posx <= 20 && movingleft)
	{
		for (int i = 0; i < NumOfEnemies; i++)
			enemies[i].enemy.setPosition(sf::Vector2f(enemies[i].posx, enemies[i].posy + 20));
		movingright = true;
		movingleft = false;
	}
	if (enemies[NumOfEnemies - 1].posx >= side && movingright)
	{
		for (int i = 0; i < NumOfEnemies; i++)
			enemies[i].enemy.setPosition(sf::Vector2f(enemies[i].posx, enemies[i].posy + 20));
		movingright = false;
		movingleft = true;
	}
	//the right/left statements 
		if (movingleft)
		{
			for (int i = 0; i < NumOfEnemies; i++)
			{
				enemies[i].enemy.move(sf::Vector2f(-enemies[i].speedx, 0.f));
			}
		}
		else if (movingright)
		{
			for (int i = 0; i < NumOfEnemies; i++)
				enemies[i].enemy.move(sf::Vector2f(enemies[i].speedx, 0.f));

		}
}

void SpaceInvader::PlayerMovement() {
	//setting the position of the player and containing between the borders .. also its movement
	player.posx = player.playersprite.getPosition().x;
	if (player.posx > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player.playersprite.move(sf::Vector2f(-player.speedx, 0));
	}
	if (player.posx < (side - 100))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player.playersprite.move(sf::Vector2f(player.speedx, 0));
	}
}

void SpaceInvader::bulletsFunction(sf::Event& event, float dt)
{
	//setting the delta time and delay for each bullet when it is shot by LEFT 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (bulletIndex >= NumOfBullets - 1) {
			bulletIndex = 0;
		}
		if (bulletDelay <= 0) {
			ShootBullet(dt);
			bulletDelay = bulletTimer;
		}
		else {
			bulletDelay -= 1.0f * dt;
		}
	}
	else {
		bulletDelay = 0;
	}
}

void SpaceInvader::ShootBullet(float& dt) {
	//moving the bullet FROM the player UPWARDS after it is shot
	bullets[bulletIndex].released = true;
	bullets[bulletIndex].body.setScale(sf::Vector2f(2.0f, 4.0f));
	bullets[bulletIndex].body.setPosition(player.playersprite.getPosition() + sf::Vector2f(player.playersprite.getSize().x / 2 - 2, 0));
	bullets[bulletIndex].speed = sf::Vector2f(0, -900);
	bulletIndex++;
}

void SpaceInvader::Collision(sf::RenderWindow& w,int& gameID) {
	//checking if the bullet hit the enemy or not (By going through all the bullets and all the enemies)
	for (int i = 0; i < NumOfBullets; i++) {
		for (int j = 0; j < NumOfEnemies; j++) {
			if (bullets[i].body.getGlobalBounds().intersects(enemies[j].enemy.getGlobalBounds())) {
				enemies[j].enemy.setScale(sf::Vector2f(0.f, 0.f));
				bullets[i].released = false;
				score++;
				scoretext.setString("Score: " + to_string(score));
			}
		}
	}
	//checking if the enemy hits the player or if the score is max(All enemies are hit)
	for (int i = 0; i < NumOfEnemies; i++) {
		if (enemies[i].enemy.getScale().x != 0 && enemies[i].enemy.getScale().y != 0) 
			if (enemies[i].enemy.getGlobalBounds().intersects(player.playersprite.getGlobalBounds()))
				gameID = 0;
		
		if (score == NumOfEnemies)
			gameID = 0;
	}
}


void SpaceInvader::Run(sf::RenderWindow& win, int& score, sf::Event& e, float& dt,int& gameID) {
	for (int i = 0; i < NumOfEnemies; i++)
		win.draw(enemies[i].enemy);
	for (int i = 0; i < NumOfBullets; i++) {
		bullets[i].Update(dt);
		win.draw(bullets[i].body);
	}
	win.draw(player.playersprite);
	win.draw(scoretext);
	bulletsFunction(e, dt);
	EnemyMovement();
	PlayerMovement();
	Collision(win,gameID);
}

void Bullet::Update(float& dt) {
	if (!released) {
		body.setScale(sf::Vector2f(0, 0));
	}
	else {
		body.setScale(sf::Vector2f(2.0f, 4.0f));
	}
	body.move(speed * dt);
}