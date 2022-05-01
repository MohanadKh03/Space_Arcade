#include "Duck.h"
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>

using namespace std;

Text test;

SoundBuffer duckExpo;
Sound ExpolosionDuck(duckExpo);


Duck::Duck(RenderWindow& window) {

	duckExpo.loadFromFile("Duck explosion.wav");
	// special effects calls  /////////////////////////////////////////
	hitEffectTex.loadFromFile("Explosion Red.png");
	hitEffect.setTexture(hitEffectTex);
	hitEffect.setOrigin(64, 64);
	hitEffect.setScale(Vector2f(window.getSize().x / 700, window.getSize().x / 700));

	background.loadFromFile("Space Background.png");
	backgroundsp.setTexture(background);
	crosshair.setSize(Vector2f(35, 35));
	crosshair.setFillColor(Color::Red);
	cross.loadFromFile("SeekPng.com_crosshair-png_140906.png");
	crosshair.setTexture(&cross);
	crosshair.setOrigin(Vector2f(crosshair.getSize().x / 2, crosshair.getSize().y / 2));
	font.loadFromFile("fonts/BodoniFLF-Bold.ttf");
	score_text.setFont(font);
	score_text.setPosition(500.0f, 0.f);
	text.setFont(font);
	text.setPosition(0.f, 0.f);

	test.setFont(font);
	test.setString(to_string(friendliesCount));
	test.setPosition(300.0f, 0.f);

	for (int i = 0; i < 20; i++)
	{
		texture_index = rand() % 7;
		switch (texture_index)
		{
		case 0:
			enemies[i].texture1.loadFromFile("Enemy1.png");
			enemies[i].duck.setTexture(&enemies[i].texture1);
			enemies[i].duck.setScale(2.0,2.0);
			friendlies[i].texture5.loadFromFile("Friendly1.png");
			friendlies[i].duck.setTexture(&friendlies[i].texture5);
			friendlies[i].duck.setScale(2.0, 2.0);
			break;
		case 1:
			enemies[i].texture2.loadFromFile("Enemy2.png");
			enemies[i].duck.setTexture(&enemies[i].texture2);
			enemies[i].duck.setScale(2.0, 2.0);
			friendlies[i].texture6.loadFromFile("Friendly2.png");
			friendlies[i].duck.setTexture(&friendlies[i].texture6);
			friendlies[i].duck.setScale(2.0, 2.0);
			break;
		case 2:
			enemies[i].texture3.loadFromFile("Enemy3.png");
			enemies[i].duck.setTexture(&enemies[i].texture3);
			enemies[i].duck.setScale(2.0, 2.0);
			friendlies[i].texture7.loadFromFile("Friendly3.png");
			friendlies[i].duck.setTexture(&friendlies[i].texture7);
			friendlies[i].duck.setScale(2.0, 2.0);
			break;
		case 3:
			enemies[i].texture4.loadFromFile("Enemy4.png");
			enemies[i].duck.setTexture(&enemies[i].texture4);
			enemies[i].duck.setScale(2.0, 2.0);
			break;
		
		}
	}
	for (int i = 0; i < 20; i++)
	{
		texture_index = rand() % 3;
		switch (texture_index)
		{
		case 0:
			
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		}
	}
	/*dead.setFont(font);
	dead.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
*/
}

void Duck::Update(RenderWindow& window, Event& e, float& dt, int& gameID) {
	window.draw(backgroundsp);
	if (health >= 0) {
		if (e.type == Event::MouseMoved) {
			crosshair.setPosition(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (!pressed) {
				for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
					if (enemies[i].duck.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && enemies[i].alive) {
						playEffect(enemies[i].duck.getPosition() + Vector2f(enemies[i].duck.getSize().x / 2, enemies[i].duck.getSize().y / 2));
						score++;
						enemiesCount--;
						enemies[i].alive = false;
						ExpolosionDuck.play();
					}
				}
				pressed = true;
			}
		}
		else {
			pressed = false;
		}

		hitEffect.setTextureRect(IntRect(spriteIndex * 128, 0, 128, 128));
		if (enemyDelay <= 0) {
			SpawnShips(window);
			enemyDelay = delay;
		}
		else {
			enemyDelay -= 1 * dt;
		}
		for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
			if (enemies[i].alive) {
				enemies[i].Update(window, dt, health, enemiesCount, friendliesCount);
			}
		}

		text.setString("Health" + to_string(health));
		score_text.setString("Score" + to_string(score));
	}
	//Nour
	if (effectTimer <= 0 && spriteIndex < 8) {
		spriteIndex++;
		effectTimer = effectDelay;
	}
	else
	{
		effectTimer -= 1 * delay;
	}

	Render(window, gameID);
}

void Duck::SpawnShips(RenderWindow& window) {

	if (enemiesCount < maxEnemies) {
		for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
			if (!enemies[i].alive && enemiesCount < maxEnemies) {
				directionIndex = rand() % 4;
				switch (directionIndex)
				{
				case 0:
					positionIndex = rand() % (int)(window.getSize().x - (window.getSize().x * 0.2f)) + window.getSize().x * 0.1f;
					enemies[i].speed = Vector2f(0, shipSpeed);
					enemies[i].position = Vector2f(positionIndex, -10.0f);
					enemies[i].duck.setScale(abs(enemies[i].duck.getScale().x), abs(enemies[i].duck.getScale().y));
					enemies[i].duck.setRotation(180);
					break;
				case 1:
					positionIndex = rand() % (int)(window.getSize().y - (window.getSize().y * 0.2f)) + window.getSize().y * 0.1f;
					enemies[i].speed = Vector2f(-shipSpeed, 0);
					enemies[i].position = Vector2f(window.getSize().x + 10.0f, positionIndex);
					enemies[i].duck.setScale(abs(enemies[i].duck.getScale().x), abs(enemies[i].duck.getScale().y));
					enemies[i].duck.setRotation(-90);
					break;
				case 2:
					positionIndex = rand() % (int)(window.getSize().x - (window.getSize().x * 0.2f)) + window.getSize().x * 0.1f;
					enemies[i].speed = Vector2f(0, -shipSpeed);
					enemies[i].position = Vector2f(positionIndex, window.getSize().y + 10.0f);
					enemies[i].duck.setScale(abs(enemies[i].duck.getScale().x), abs(enemies[i].duck.getScale().y));
					enemies[i].duck.setRotation(0);
					break;
				case 3:
					positionIndex = rand() % (int)(window.getSize().y - (window.getSize().y * 0.2f)) + window.getSize().y * 0.1f;
					enemies[i].speed = Vector2f(shipSpeed, 0);
					enemies[i].position = Vector2f(-10.0f, positionIndex);
					enemies[i].duck.setScale(-abs(enemies[i].duck.getScale().x), abs(enemies[i].duck.getScale().y));
					enemies[i].duck.setRotation(90);
					break;
				}
				enemies[i].duck.setPosition(enemies[i].position);
				enemiesCount++;
				enemies[i].alive = true;
			}
		}
	}
	if (friendliesCount < maxFriendlies)
	{
		for (int i = 0; i < (sizeof(friendlies) / sizeof(friendlies[i])); i++)
		{
			if (!friendlies[i].alive && friendliesCount < maxFriendlies)
			{
				int x = rand() % 4;
				switch (x)
				{
				case 0:
					positionIndex = rand() % (int)(window.getSize().x - (window.getSize().x * 0.2f)) + window.getSize().x * 0.1f;
					friendlies[i].speed = Vector2f(0, shipSpeed);
					friendlies[i].position = Vector2f(positionIndex, -10.0f);
					friendlies[i].duck.setScale(abs(friendlies[i].duck.getScale().x), abs(friendlies[i].duck.getScale().y));
					friendlies[i].duck.setRotation(180);
					break;
				case 1:
					positionIndex = rand() % (int)(window.getSize().y - (window.getSize().y * 0.2f)) + window.getSize().y * 0.1f;
					friendlies[i].speed = Vector2f(-shipSpeed, 0);
					friendlies[i].position = Vector2f(window.getSize().x + 10.0f, positionIndex);
					friendlies[i].duck.setScale(abs(friendlies[i].duck.getScale().x), abs(friendlies[i].duck.getScale().y));
					friendlies[i].duck.setRotation(-90);
					break;
				case 2:
					positionIndex = rand() % (int)(window.getSize().x - (window.getSize().x * 0.2f)) + window.getSize().x * 0.1f;
					friendlies[i].speed = Vector2f(0, -shipSpeed);
					friendlies[i].position = Vector2f(positionIndex, window.getSize().y + 10.0f);
					friendlies[i].duck.setScale(abs(friendlies[i].duck.getScale().x), abs(friendlies[i].duck.getScale().y));
					friendlies[i].duck.setRotation(0);
					break;
				case 3:
					positionIndex = rand() % (int)(window.getSize().y - (window.getSize().y * 0.2f)) + window.getSize().y * 0.1f;
					friendlies[i].speed = Vector2f(shipSpeed, 0);
					friendlies[i].position = Vector2f(-10.0f, positionIndex);
					friendlies[i].duck.setScale(-abs(friendlies[i].duck.getScale().x), abs(friendlies[i].duck.getScale().y));
					friendlies[i].duck.setRotation(90);
					break;
				}
				friendlies[i].duck.setPosition(friendlies[i].position);
				friendliesCount++;
				friendlies[i].alive = true;
			}
		}
	}
}

void Duck::Render(RenderWindow& window, int& gameID)
{
	window.draw(crosshair);
	window.draw(test);
	window.draw(text);
	window.draw(score_text);
	window.draw(hitEffect);
	if (health <= 0)
		gameID = 0;

}


Ship::Ship() {
	duck.setSize(Vector2f(100, 100));
	duck.setFillColor(Color::White);
	duck.setPosition(position);
}

void Ship::Update(RenderWindow& window, float& dt, int& health, int& enemiesCount, int& friendliesCount)
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

void Ship::Death_Check(RenderWindow& window) {
	if (check_in)
		return;
	if (duck.getPosition().x >= 30 && duck.getPosition().y >= 30
		&& duck.getPosition().x <= window.getSize().x - 30 && duck.getPosition().y <= window.getSize().y - 30)
		check_in = true;
}


// Play the splash effect
void Duck::playEffect(Vector2f position)
{
	effectTimer = effectDelay;
	spriteIndex = 0;
	hitEffect.setPosition(position);
	//hitEffect.setRotation(rotation);
}