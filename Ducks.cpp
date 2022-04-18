#include "Duck.h"
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;

Duck::Duck(RenderWindow& window) {
	crosshair.setSize(Vector2f(5, 5));
	crosshair.setFillColor(Color::Red);
	crosshair.setOrigin(Vector2f(crosshair.getSize().x / 2, crosshair.getSize().y / 2));
	font.loadFromFile("fonts/BodoniFLF-Bold.ttf");
	score_text.setFont(font);
	score_text.setPosition(500.0f, 0.f);
	text.setFont(font);
	text.setPosition(0.f, 0.f);
	/*dead.setFont(font);
	dead.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);*/
	
}

void Duck::Update(RenderWindow& window, Event& e, float& dt,int& gameID) {
	if (health >= 0) {
		if (e.type == Event::MouseMoved) {
			crosshair.setPosition(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (!pressed) {
				for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
					if (enemies[i].duck.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && enemies[i].alive) {
						score++;
						enemiesCount--;
						enemies[i].alive = false;
					}
				}
				pressed = true;
			}
		}
		else {
			pressed = false;
		}
		if (enemyDelay <= 0) {
			SpawnEnemy(window);
			enemyDelay = delay;
		}
		else {
			enemyDelay -= 1 * dt;
		}
		for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
			if (enemies[i].alive) {
				enemies[i].Update(window, dt, health, enemiesCount);
			}
		}
		
			text.setString("Health" + to_string(health));
			score_text.setString("Score" + to_string(score));
	}
	Render(window,gameID);
}

void Duck::SpawnEnemy(RenderWindow& window) {
	if (enemiesCount < maxEnemies) {
		for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
			if (!enemies[i].alive && enemiesCount < maxEnemies) {
				directionIndex = rand() % 4;
				switch (directionIndex)
				{
				case 0:
					positionIndex = rand() % window.getSize().x;
					enemies[i].speed = Vector2f(0, enemySpeed);
					enemies[i].position = Vector2f(positionIndex, -10.0f);
					break;
				case 1:
					positionIndex = rand() % window.getSize().y;
					enemies[i].speed = Vector2f(-enemySpeed, 0);
					enemies[i].position = Vector2f(window.getSize().x + 10.0f, positionIndex);
					break;
				case 2:
					positionIndex = rand() % window.getSize().x;
					enemies[i].speed = Vector2f(0, -enemySpeed);
					enemies[i].position = Vector2f(positionIndex, window.getSize().y + 10.0f);
					break;
				case 3:
					positionIndex = rand() % window.getSize().y;
					enemies[i].speed = Vector2f(enemySpeed, 0);
					enemies[i].position = Vector2f(-10.0f, positionIndex);
					break;
				}
				enemies[i].duck.setPosition(enemies[i].position);
				enemiesCount++;
				enemies[i].alive = true;
			}
		}
	}
}

void Duck::Render(RenderWindow& window,int& gameID)
{
	window.draw(crosshair);
	window.draw(text);
	window.draw(score_text);
	if (health <= 0) 
		gameID = 0;
	
}

Enemy::Enemy() {
	duck.setSize(Vector2f(100, 100));
	duck.setFillColor(Color::White);
	duck.setPosition(position);
}

void Enemy::Update(RenderWindow& window, float& dt, int& health, int& enemiesCount)
{
	duck.move(speed * dt);
	Death_Check(window);
	if (check_in) {
		if (speed.x > 0) {
			if (duck.getPosition().x >= window.getSize().x + 100) {
				alive = false;
				health--;
				enemiesCount--;
			}
		}
		else if (speed.x < 0) {
			if (duck.getPosition().x <= -100) {
				alive = false;
				health--;
				enemiesCount--;
			}
		}
		else if (speed.y > 0) {
			if (duck.getPosition().y >= window.getSize().y + 100) {
				alive = false;
				health--;
				enemiesCount--;
			}
		}
		else if (speed.y < 0) {
			if (duck.getPosition().y <= -100) {
				alive = false;
				health--;
				enemiesCount--;
			}
		}
	}
	window.draw(duck);
}

void Enemy::Death_Check(RenderWindow& window) {
	if (check_in)
		return;
	if (duck.getPosition().x >= 30 && duck.getPosition().y >= 30
		&& duck.getPosition().x <= window.getSize().x - 30 && duck.getPosition().y <= window.getSize().y - 30)
		check_in = true;
}
