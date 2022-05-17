#include "Duck.h"
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>

using namespace std;
//Testing
Text test;
bool gameStart = true;
Text start;
Font duckMenu;
Event eve;
//

SoundBuffer duckExpo;
Sound ExpolosionDuck(duckExpo);


SoundBuffer hahaSound;
Sound haha(hahaSound);


Duck::Duck(RenderWindow& window) {
	score = 0;
	duckMenu.loadFromFile("Fonts/AshetyPersonaluse-Medium.otf");
	
	hahaSound.loadFromFile("Sounds/Duck/haha.wav");
	haha.setVolume(50.0);

	duckExpo.loadFromFile("Sounds/Duck/Duck explosion.wav");
	ExpolosionDuck.setVolume(60.0);

	// special effects calls  /////////////////////////////////////////
	hitEffectTex.loadFromFile("Textures/Duck/Explosion Red.png");
	hitEffect.setTexture(hitEffectTex);
	hitEffect.setOrigin(64, 64);
	hitEffect.setScale(Vector2f((float)window.getSize().x / 700, (float)window.getSize().x / 700));

	background.loadFromFile("Textures/Duck/Space Background2.png");
	backgroundsp.setTexture(background);


	crosshair.setSize(Vector2f(35, 35));
	crosshair.setFillColor(Color::Red);
	cross.loadFromFile("Textures/Duck/SeekPng.com_crosshair-png_140906.png");
	crosshair.setTexture(&cross);
	crosshair.setOrigin(Vector2f(crosshair.getSize().x / 2, crosshair.getSize().y / 2));
	
	font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
	
	score_text.setFont(font);
	score_text.setPosition(500.0f, 0.f);
	text.setFont(font);
	text.setPosition(0.f, 0.f);

	/*test.setFont(font);
	test.setPosition(300.0f, 0.f);*/

	enemies[0].friendly = false;
	enemies[0].texture1.loadFromFile("Textures/Duck/Enemy1.png");
	enemies[0].duck.setTexture(&enemies[0].texture1);
	enemies[0].duck.setScale(enemiesScale);

	for (int i = 1; i < 20; i++)
	{
		friend_index = rand() % 2;
		if (friendliesMaxCount > 0) {
			switch (friend_index)
			{
			case 0:
				enemies[i].friendly = true;
				friendliesMaxCount--;
				break;
			case 1:
				enemies[i].friendly = false;
				break;
			}
		}
		else {
			enemies[i].friendly = false;
		}
		texture_index = rand() % 4;
		switch (texture_index)
		{
		case 0:
			if (enemies[i].friendly) {
				enemies[i].texture5.loadFromFile("Textures/Duck/Friendly1.png");
				enemies[i].duck.setTexture(&enemies[i].texture5);
			}
			else {
				enemies[i].texture1.loadFromFile("Textures/Duck/Enemy1.png");
				enemies[i].duck.setTexture(&enemies[i].texture1);
			}
			enemies[i].duck.setScale(enemiesScale);
			break;
		case 1:
			if (enemies[i].friendly) {
				enemies[i].texture6.loadFromFile("Textures/Duck/Friendly2.png");
				enemies[i].duck.setTexture(&enemies[i].texture6);
			}
			else {
				enemies[i].duck.setTexture(&enemies[i].texture2);
				enemies[i].texture2.loadFromFile("Textures/Duck/Enemy2.png");
			}
			enemies[i].duck.setScale(enemiesScale);
			break;
		case 2:
			if (enemies[i].friendly) {
				enemies[i].texture7.loadFromFile("Textures/Duck/Friendly3.png");
				enemies[i].duck.setTexture(&enemies[i].texture7);
			}
			else {
				enemies[i].texture3.loadFromFile("Textures/Duck/Enemy3.png");
				enemies[i].duck.setTexture(&enemies[i].texture3);
			}
			enemies[i].duck.setScale(enemiesScale);
			break;
		case 3:
			enemies[i].friendly = false;
			enemies[i].texture4.loadFromFile("Textures/Duck/Enemy4.png");
			enemies[i].duck.setTexture(&enemies[i].texture4);
			enemies[i].duck.setScale(enemiesScale);
			break;
		}
	}

	DuckGame.openFromFile("Sounds/Duck/127706__cydon__spacebattle-with-laserwaepons001.wav");
	DuckGame.setLoop(true);
	DuckGame.setVolume(30.0);
	DuckGame.play();
}

void Duck::Update(RenderWindow& window, Event& e, float& dt, int& gameID, int& GAMEscore) {
	window.draw(backgroundsp);
	GAMEscore = score;
	if (health >= 0) {
		if (e.type == Event::MouseMoved) {
			crosshair.setPosition(Vector2f((float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y));
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {

			if (!pressed) {
				for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
					if (enemies[i].duck.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && enemies[i].alive) {
						playEffect(crosshair.getPosition());
						if (!enemies[i].friendly) {
							ExpolosionDuck.play();
							score++;
						}
						else {
							haha.play();
							health--;
						}
						
						enemies[i].alive = false;
						enemiesCount--;
					}
				}
				pressed = true;
			}
		}
		else {
			pressed = false;
		}

		// Leveling
		if (score >= 1 && level == 0) {
			maxEnemies = 4;
			level=1;
		}
		else if (score >= 10 && level == 1) {
			maxEnemies = 8;
			level=2;
		}
		else if (score >= 20 && level == 2) {
			maxEnemies = 12;
			level=3;
		}
		else if (score >= 30 && level == 3) {
			maxEnemies = 16;
			level=4;
		}
		else if (score >= 40 && level == 4) {
			maxEnemies = 20;
			level=5;
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
				enemies[i].Update(window, dt, health, enemiesCount);
			}
		}


		text.setString("Health: " + to_string(health));
		score_text.setString("Score: " + to_string(score));
	}
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
	float windowX = (float)window.getSize().x;
	float windowY = (float)window.getSize().y;
	if (enemiesCount <= maxEnemies) {
		for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
			if (!enemies[i].alive && enemiesCount < maxEnemies) {
				directionIndex = rand() % 4;
				if (enemies[i].friendly)
					shipSpeed = 400.0f;
				else
					shipSpeed = 200.0f;
				switch (directionIndex)
				{
				case 0:
					positionIndex = (int)(rand() % (int)(windowX - (windowX * 0.2f)) + windowX * 0.1f);
					enemies[i].speed = Vector2f(0, shipSpeed);
					enemies[i].position = Vector2f((float)positionIndex, -10.0f);
					enemies[i].duck.setScale(abs(enemies[i].duck.getScale().x), abs(enemies[i].duck.getScale().y));
					enemies[i].duck.setRotation(180);
					break;
				case 1:
					positionIndex = (int)(rand() % (int)(windowY - (windowY * 0.2f)) + windowY * 0.1f);
					enemies[i].speed = Vector2f(-shipSpeed, 0);
					enemies[i].position = Vector2f(windowX + 10.0f, (float)positionIndex);
					enemies[i].duck.setScale(abs(enemies[i].duck.getScale().x), abs(enemies[i].duck.getScale().y));
					enemies[i].duck.setRotation(-90);
					break;
				case 2:
					positionIndex = (int)(rand() % (int)(windowX - (windowX * 0.2f)) + windowX * 0.1f);
					enemies[i].speed = Vector2f(0, -shipSpeed);
					enemies[i].position = Vector2f((float)positionIndex, windowY + 10.0f);
					enemies[i].duck.setScale(abs(enemies[i].duck.getScale().x), abs(enemies[i].duck.getScale().y));
					enemies[i].duck.setRotation(0);
					break;
				case 3:
					positionIndex = (int)(rand() % (int)(windowY - (windowY * 0.2f)) + windowY * 0.1f);
					enemies[i].speed = Vector2f(shipSpeed, 0);
					enemies[i].position = Vector2f(-10.0f, (float)positionIndex);
					enemies[i].duck.setScale(-abs(enemies[i].duck.getScale().x), abs(enemies[i].duck.getScale().y));
					enemies[i].duck.setRotation(90);
					break;
				}
				enemies[i].duck.setPosition(enemies[i].position);
				enemies[i].alive = true;
				enemiesCount++;
			}
		}
	}
}

void Duck::Render(RenderWindow& window, int& gameID)
{
		
		window.draw(start);
	
		window.draw(crosshair);
		
		window.draw(text);
		window.draw(score_text);
		window.draw(hitEffect);
	
		if (health <= 0) {
			gameID = 0;
			
		}

}


Ship::Ship() {
	duck.setSize(Vector2f(100, 100));
	duck.setFillColor(Color::White);
	duck.setPosition(position);
	if (friendly) {

	}
	else {

	}
}

void Ship::Update(RenderWindow& window, float& dt, int& health, int& enemiesCount)
{
	duck.move(speed * dt);
	Death_Check(window);
	if (check_in) {
		if (speed.x > 0) {
			if (duck.getPosition().x >= (float)window.getSize().x + 300) {
				alive = false;
				if(!friendly)
				{
					health--;
				}
				enemiesCount--;
			}
		}
		else if (speed.x < 0) {
			if (duck.getPosition().x <= -300) {
				alive = false;
				if (!friendly)
				{
					health--;
				}
				enemiesCount--;
			}
		}
		else if (speed.y > 0) {
			if (duck.getPosition().y >= (float)window.getSize().y + 300) {
				alive = false;
				if (!friendly)
				{
					health--;
				}
				enemiesCount--;
			}
		}
		else if (speed.y < 0) {
			if (duck.getPosition().y <= -300) {
				alive = false;
				if (!friendly)
				{
					health--;
				}
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
		&& duck.getPosition().x <= (float)window.getSize().x - 30 && duck.getPosition().y <= (float)window.getSize().y - 30)
		check_in = true;
}


// Play the splash effect
void Duck::playEffect(Vector2f position)
{
	effectTimer = effectDelay;
	spriteIndex = 0;
	hitEffect.setPosition(position);
}