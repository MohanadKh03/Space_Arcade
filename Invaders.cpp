#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include "Invaders.h"
using namespace std;
using namespace sf;

bool movingright = true;
bool movingleft = false;
float windowsizex = (float)VideoMode::getDesktopMode().width;
float windowsizey = (float)VideoMode::getDesktopMode().height;
int side = VideoMode::getDesktopMode().width - 120;
int z = 0;

SpaceInvader::SpaceInvader(RenderWindow& window) {

	//background music
	backgroundMusic.openFromFile("Sounds/Space-Invaders/Backtheme.wav");
	backgroundMusic.setLoop(true);
	//sheild stuff
	sheilds[0].sprite.setPosition(50, (float)VideoMode::getDesktopMode().height - (float)VideoMode::getDesktopMode().height / 4);

	for (int i = 0; i < 2; i++)
	{
		if (i > 0)
			sheilds[i].sprite.setPosition(sheilds[i - 1].sprite.getPosition().x +(window.getSize().x - sheilds[i - 1].sprite.getSize().x) - 65, sheilds[i - 1].sprite.getPosition().y);
		sheilds[i].texture.loadFromFile("Textures/Space Invaders/Shield.png");
		sheilds[i].sprite.setTexture(&sheilds[i].texture);
		sheilds[i].health = 100;
		sheilds[i].sprite.setSize(Vector2f(400.f, 100.f));
		sheilds[i].active = true;

	}
	//show the score
	GameOverText.setPosition(Vector2f(windowsizex / 2 - 80 * WindowFactor, windowsizey / 2));
	GameOverFont.loadFromFile("Fonts/ARCADE_R.ttf");
	GameOverText.setFont(GameOverFont);
	GameOverText.setFillColor(Color(255, 0, 0));
	score = 0;
	scoretext.setPosition(Vector2f((float)window.getSize().x - 300.f, 0));
	scoretext.setString("Score: " + to_string(score));
	scorefont.loadFromFile("Fonts/ARCADE_R.ttf");
	scoretext.setFont(scorefont);
	scoretext.setFillColor(Color(0, 255, 0));
	livestext.setPosition(Vector2f((float)window.getSize().x - 300.f, scoretext.getScale().y + 50));
	livestext.setString("Lives " + to_string(5));
	livesfont.loadFromFile("Fonts/ARCADE_R.ttf");
	livestext.setFont(livesfont);
	livestext.setFillColor(Color(0, 255, 255));
	for (int i = 0; i < 2; i++)
	{
		SheildText[i].setPosition(sheilds[i].sprite.getPosition());
		SheildFont[i].loadFromFile("Fonts/ARCADE_R.ttf");
		SheildText[i].setFont(SheildFont[i]);
		SheildText[i].setFillColor(Color(Color::Red));
		SheildText[i].setString(to_string(sheilds[i].health)+ "%");
	}


	srand(time(0));

	//boss stuff
	boss.BossTexture.loadFromFile("Textures/Space Invaders/enemyBlack.png");
	boss.BossMissle = new Texture;
	boss.BossMissle -> loadFromFile("Textures/Space Invaders/My project.png");
	boss.bossMissle.setTexture(*boss.BossMissle);
	boss.bossMissle.setRotation(180);
	boss.bossMissle.setPosition(Vector2f(128,128));
	
	boss.Boss.setTexture(boss.BossTexture);
	boss.Boss.setScale(Vector2f(2, 3));
	boss.Boss.setPosition(Vector2f(-120, 0));
	boss.Boss.setColor(Color(0, 255, 255, 0));
	boss.isBossActive = false;
	boss.isMovingright = true;
	ReleaseBoss = false;
	boss.bossGenCounter = 0;

	//background
	background.loadFromFile("Textures/Space Invaders/stars_texture.png");
	backgroundsprite.setTexture(background);
	//sprite Stuff
	enemies[0].health = 100;
	enemies[0].pos.x = 20;
	enemies[0].pos.y = 0;
	enemies[0].texture.loadFromFile("Textures/Space Invaders/Enemy1.png");
	enemies[0].sprite.setTexture(enemies[0].texture);
	enemies[0].sprite.setScale(Vector2f(1.3f * WindowFactor, 1.3f * WindowFactor));
	enemies[0].bulletBuffer.loadFromFile("Sounds/Space-Invaders/EnemyBulletBuffer.wav");
	enemies[0].bulletSound.setBuffer(enemies[0].bulletBuffer);
	enemies[0].sprite.setPosition(Vector2f(enemies[0].pos.x, enemies[0].pos.y));
	enemies[0].sprite.setColor(Color(enemies[0].sprite.getColor().r, enemies[0].sprite.getColor().b, enemies[0].sprite.getColor().g, 240));
	enemies[0].bullet.sprite.setFillColor(Color(0, 255, 0, 255));
	enemies[0].bullet.sprite.setSize(Vector2f(enemies[0].sprite.getGlobalBounds().width * 0.06294117f, enemies[0].sprite.getGlobalBounds().width * 0.10294117f * 4.5f));
	enemies[0].bullet.sprite.setPosition(enemies[0].sprite.getPosition().x + 46.5f, enemies[0].sprite.getPosition().y + 42);
	laser.loadFromFile("Textures/Space Invaders/PlayerLaser.png");
	Sprite bulletBuffer(laser);
	bulletBuffer.setTextureRect(IntRect(0, 0, 32, 32));
	/*enemies[0].enemypower.sprite.setRadius(3.f);
	enemies[0].enemypower.sprite.setPosition(enemies[0].sprite.getPosition());
	enemies[0].enemypower.sprite.setFillColor(Color(0, 255, 255, 0));
	enemies[0].enemypower.powerConsumed = false;
	enemies[0].enemypower.fireRate == false;*/
	for (int i = 1; i < NumOfEnemies; i++)
	{

		enemies[i].health = 100;
		enemies[i].texture.loadFromFile("Textures/Space Invaders/Enemy1.png");
		enemies[i].sprite.setTexture(enemies[i].texture);;
		enemies[i].sprite.setScale(Vector2f(1.3f * WindowFactor, 1.3f * WindowFactor));
		enemies[i].bulletBuffer.loadFromFile("Sounds/Space-Invaders/EnemyBulletBuffer.wav");
		enemies[i].bulletSound.setBuffer(enemies[i].bulletBuffer);
		enemies[i].bullet.sprite.setFillColor(Color(0, 0, 255, 255));
		enemies[i].bullet.sprite.setSize(Vector2f(enemies[0].sprite.getGlobalBounds().width * 0.06294117f, enemies[0].sprite.getGlobalBounds().width * 0.10294117f * 4.5f));
		enemies[i].bullet.released = false;
		enemies[i].bullet.sprite.setPosition(enemies[i].sprite.getPosition().x + 46.5f, enemies[i].sprite.getPosition().y + 42);
		//enemies[i].bullet.sprite.setScale(Vector2f(2.f, 4.f));
		/*enemies[i].enemypower.sprite.setRadius(3.f);
		enemies[i].enemypower.sprite.setPosition(enemies[i].sprite.getPosition());
		enemies[i].enemypower.sprite.setFillColor(Color(0, 255, 255, 0));
		enemies[i].enemypower.powerConsumed = false;
		enemies[i].enemypower.fireRate == false;*/
		if (  i % 10 != 0)
		{
			enemies[i].pos.x = enemies[i - 1].pos.x + 90 * WindowFactor;
			enemies[i].pos.y = enemies[i - 1].pos.y;
		}
		else if (i % 10 == 0)
		{
			enemies[i].pos.x = enemies[0].pos.x;
			enemies[i].pos.y = enemies[i - 1].pos.y + 90 * WindowFactor;
		}

		enemies[i].sprite.setPosition(Vector2f(enemies[i].pos.x, enemies[i].pos.y));
	}
	//Player Stuff
	player.pos.x = (float)VideoMode::getDesktopMode().width / 2;
	player.pos.y = (float)VideoMode::getDesktopMode().height - 100 * WindowFactor;
	player.texture.loadFromFile("Textures/Space Invaders/SpaceShipPlayer.png");
	player.bulletBuffer.loadFromFile("Sounds/Space-Invaders/PlayerBulletBuffer.wav");
	player.bulletSound.setBuffer(player.bulletBuffer);
	player.sprite.setTexture(&player.texture);
	player.sprite.setSize(Vector2f((float)window.getSize().x / 19.68f, (float)window.getSize().y / 11.f));
	player.sprite.setPosition(Vector2f(player.pos.x, player.pos.y));
	player.health = 5;
	//Bullets stuff
	for (int i = 0; i < NumOfBullets; i++)
	{
		float bulletPositionX = 0.0f;
		int bulletPos = rand() % 2;
		switch (bulletPos)
		{	
		case 0:
			bulletPositionX = player.sprite.getSize().x * 0.90f;
			break;
		case 1:
			bulletPositionX = player.sprite.getSize().x * 0.21f;
			break;
		}
		bullets[i].released = false;
		bullets[i].sprite.setScale(Vector2f(1.5f, 4.f));
		bullets[i].sprite.setPosition(bulletPositionX, player.pos.y);

	}
	//// Reset the score
	//score = 0;
	backgroundMusic.play();
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(100.f);

}

void SpaceInvader::EnemyMovement(float dt, Clock& clock, Time& deltatimemove)
{
	//setting the x,y positions for the already set in the constructor ones
	deltatimemove = clock.getElapsedTime();

	for (int i = 0; i < NumOfEnemies; i++)
	{
		if (enemies[i].bullet.released == false)
			enemies[i].bullet.sprite.setPosition(enemies[i].pos.x + 46.5f, enemies[i].pos.y + 38);
		/*if (enemies[i].enemypower.powerSpared == false)
			enemies[i].enemypower.sprite.setPosition(enemies[i].sprite.getPosition());*/
		 
		enemies[i].pos.x = enemies[i].sprite.getPosition().x;
		enemies[i].pos.y = enemies[i].sprite.getPosition().y;
	}


	//containing the enemies and moving them right/left and down if they reach the far end(right/left)
	//the down statement with right and left booleans
	if (enemies[0].pos.x <= 20 && movingleft)
	{
		for (int i = 0; i < NumOfEnemies; i++)
			enemies[i].sprite.setPosition(Vector2f(enemies[i].pos.x, enemies[i].pos.y + 60));
		movingright = true;
		movingleft = false;
	}
	if (enemies[NumOfEnemies - 1].pos.x >= side && movingright)
	{
		for (int i = 0; i < NumOfEnemies; i++)
			enemies[i].sprite.setPosition(Vector2f(enemies[i].pos.x, enemies[i].pos.y + 60));
		movingright = false;
		movingleft = true;
	}


	//the right/left statements 
	if (movingleft && deltatimemove.asMilliseconds() >= 500)
	{
		for (int i = 0; i < NumOfEnemies; i++)
		{
			enemies[i].sprite.setPosition(Vector2f(enemies[i].pos.x - 30, enemies[i].pos.y));
		}
		clock.restart();
	}
	else if (movingright && deltatimemove.asMilliseconds() >= 500)
	{
		for (int i = 0; i < NumOfEnemies; i++)
			enemies[i].sprite.setPosition(Vector2f(enemies[i].pos.x + 30, enemies[i].pos.y));
		clock.restart();
	}

}

void SpaceInvader::PlayerMovement() {
	//setting the position of the player and containing between the borders .. also its movement
	player.pos.x = player.sprite.getPosition().x;


	//stop player from getting out of screen
	if (sf::Mouse::getPosition().x > windowsizex - player.playersprite.getGlobalBounds().width)
		sf::Mouse::setPosition(sf::Vector2i(int(windowsizex - player.playersprite.getGlobalBounds().width), 0));


	player.sprite.setPosition(Vector2f((float)Mouse::getPosition().x, player.pos.y));
}

void SpaceInvader::bulletsFunction(Event& event, float dt)
{
	//setting the delta time and delay for each bullet when it is shot by LEFT 
	if (Mouse::isButtonPressed(Mouse::Left)) {
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
	else
	{
		bulletDelay = 0;
	}
}

void SpaceInvader::ShootBullet(float& dt) {
	//moving the bullet FROM the player UPWARDS after it is shot
	bullets[bulletIndex].released = true;
	player.bulletSound.play();
	bullets[bulletIndex].sprite.setSize(Vector2f(20.f, 40.f));
	bullets[bulletIndex].sprite.setPosition(player.sprite.getPosition() + Vector2f(player.sprite.getSize().x / 2 - 2, 0));
	bullets[bulletIndex].speed = Vector2f(0, -900);
	bulletIndex++;
}

void SpaceInvader::Collision(RenderWindow& w, int& gameID) {
	//checking if the bullet hit the sprite or not (By going through all the bullets and all the enemies)
	for (int i = 0; i < NumOfEnemies; i++)
	{
		if (enemies[i].bullet.sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
		{
			player.Damaged = true;
			--player.health;
			enemies[i].bullet.released = false;
			enemies[i].bullet.sprite.setFillColor(Color(0, 255, 0, 0));
			livestext.setString("Lives " + to_string(player.health));
		}
		else
		{
			player.Damaged = false;

		}

	}
	for (int i = 0; i < NumOfBullets; i++)
	{

		for (int j = 0; j < NumOfEnemies; j++)
		{
			if (bullets[i].sprite.getGlobalBounds().intersects(enemies[j].sprite.getGlobalBounds()))
			{
				enemies[j].health -= 20;
				enemies[j].sprite.setColor(Color(enemies[j].red, enemies[j].sprite.getColor().g - 63, enemies[j].sprite.getColor().b - 63, enemies[j].sprite.getColor().a));
				bullets[i].released = false;
				if (enemies[j].health <= 0)
				{
					enemies[j].sprite.setScale(Vector2f(0.f, 0.f));
					score++;
					scoretext.setString("Score: " + to_string(score));
				}
				// Complete sprite change 	
			}

		}
		for (int j = 0; j < 3; j++)
		{
			if (bullets[i].sprite.getGlobalBounds().intersects(sheilds[j].sprite.getGlobalBounds()) && sheilds[j].active)
			{
				sheilds[j].health--;
				SheildText[j].setString(to_string(sheilds[j].health)+"%");
				bullets[i].released = false;
			}

		}

	}
	for (int i = 0; i < NumOfEnemies; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (enemies[i].sprite.getGlobalBounds().intersects(sheilds[j].sprite.getGlobalBounds()))
				sheilds[j].health = 0;


			if (enemies[i].bullet.sprite.getGlobalBounds().intersects(sheilds[j].sprite.getGlobalBounds()) && sheilds[j].active)
			{
				sheilds[j].health--;
				SheildText[j].setString(to_string(sheilds[j].health) + "%");
				enemies[i].bullet.sprite.setFillColor(Color(0, 255, 0, 0));
				enemies[i].bullet.released = false;
			}

		}
	}
	//checking if the sprite hits the player or if the score is max(All enemies are hit)



}

void SpaceInvader::Run(RenderWindow& win, int& GAMEscore, Event& e, float& dt, int& gameID) {
	GAMEscore = score;
 win.draw(boss.Boss);
	win.draw(backgroundsprite);
	for (int i = 0; i < NumOfEnemies; i++) {

		win.draw(enemies[i].bullet.sprite);
		win.draw(enemies[i].sprite);
		// win.draw(enemies[i].enemypower.sprite);
	}
	for (int i = 0; i < NumOfBullets; i++) {
		bullets[i].Update(dt);
		win.draw(bullets[i].sprite);
	}
	for (int i = 0; i < 3; i++)
	{
		win.draw(sheilds[i].sprite);
		win.draw(SheildText[i]);
	}
	if (SpaceInvader::isgameover == false)
	{
		win.draw(boss.bossMissle);
		win.draw(boss.Boss);
		win.draw(player.sprite);
		win.draw(scoretext);
		win.draw(livestext);
		bulletsFunction(e, dt);
		Collision(win, gameID);
		EnemyMovement(dt, clock, deltatimemove);
		PlayerMovement();
		Destroyandgen(dt);
		Boss();
		Bossmovement(karizmaBoss, KarizmaTime, dt);
		Sheild();
		/*PowerUps(dt);*/
	}
	GameOver(win, gameID);
}

void Bullet::Update(float& dt) {
	if (!released) {
		sprite.setSize(Vector2f(0, 0));
	}
	else {
		sprite.setSize(Vector2f(2.f, 4.f));
	}
	sprite.move(speed * dt);
}

void SpaceInvader::GameOver(RenderWindow& w, int& gameID)
{
	for (int i = 0; i < NumOfEnemies; i++)
	{
		if (enemies[i].sprite.getScale().x != 0 && enemies[i].sprite.getScale().y != 0)
		{
			if (enemies[i].sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()) || isgameover || player.health <= 0)
			{
				isgameover = true;
				GameOverText.setString("Game over \n Score :" + to_string(score) + "\n press Space to return");
				player.health = 100;
				w.clear();
				w.draw(GameOverText);
				if (Keyboard::isKeyPressed(Keyboard::Space))
					gameID = 0;
			}
		}
	}
	if (score == NumOfEnemies) {
		isgameover = true;
		GameOverText.setString("level won \n your new score :" + to_string(score) + "\npress space to return");
		w.clear();
		w.draw(GameOverText);
		if (Keyboard::isKeyPressed(Keyboard::Space))
			gameID = 0;
	}
	//cheats
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::B))
		score = NumOfEnemies;
	if (Keyboard::isKeyPressed(Keyboard::H))
		isgameover = true;
	if (Keyboard::isKeyPressed(Keyboard::S))
		score += 10;

}

void SpaceInvader::Destroyandgen(float dt)
{

	for (int i = 0; i < NumOfEnemies; i++)
	{
		if (enemies[i].sprite.getScale().x == 0 && !(enemies[i].bullet.released))
			enemies[i].bullet.sprite.setSize(Vector2f(0, 0));
		if (enemies[i].sprite.getScale().x == 0 && !(enemies[i].bullet.released))
			continue;
		bool lineshot;
		int linebegin = (i / 10) * 10;
		int bulletspeedgen = rand() % 11 + 2;
		for (int j = linebegin; j <= (linebegin + 11); j++)
		{

			if (enemies[j].sprite.getScale().x == 0 && !(enemies[i].bullet.released))
				continue;
			if (enemies[j].bullet.released)
			{
				lineshot = true;
				break;
			}
			else
			{
				lineshot = false;
			}
		}
		//gen
		enemies[i].shootingchance = rand() % 1000 + 1;
		if (enemies[i].shootingchance == 13)
		{

			if (!lineshot)
			{

				enemies[i].bullet.released = true;
				enemies[i].bulletspeed = bulletspeedgen * 100;
				enemies[i].bulletSound.play();

			}
		}
		if (enemies[i].bullet.released == true)
		{
			enemies[i].bullet.sprite.move(0, enemies[i].bulletspeed * dt);
			enemies[i].bullet.sprite.setFillColor(Color(0, 170, 0, 255));
		}
		//regen
		if (enemies[i].bullet.sprite.getPosition().y > VideoMode::getDesktopMode().height - 20)
		{
			enemies[i].bullet.sprite.setFillColor(Color(0, 170, 0, 0));
			enemies[i].bullet.released = false;

		}
		//destroy



	}
}

void SpaceInvader::Sheild()
{
	for (int i = 0; i < 3; i++)
	{
		if (sheilds[i].health <= 0)
		{
			sheilds[i].sprite.setFillColor(Color(0, 0, 0, 0));
			sheilds[i].active = false;
			SheildText[i].setScale(Vector2f(0, 0));
			
		}
	}
}

	void SpaceInvader::Boss()
{
		if (score >= 10)
			ReleaseBoss = true;
	if (ReleaseBoss)
	{
		boss.Boss.setColor(Color(0, 255, 255, 255));
		boss.isBossActive = true;
		boss.bossGenCounter++;
	}
}
void SpaceInvader::Bossmovement(Clock& karizmaBoss, Time& karizmatime, float dt)
{
	KarizmaTime = karizmaBoss.getElapsedTime();

	if (boss.isBossActive)
	{
		if (boss.isMovingright) {
			boss.Boss.move(Vector2f(300 * dt, 0));
			boss.wasMovingright = 1;
			boss.wasMovingleft = 0;
			karizmaBoss.restart();
		}

		if (boss.Boss.getPosition().x >= side+128 && boss.wasMovingright)
		{
			boss.isMovingright = false;
			boss.Boss.move(0, 0);
			if (KarizmaTime.asSeconds() >= 5)
				boss.isMovingleft = true;
			
		}
		if (boss.isMovingleft == true) {
			boss.Boss.move(Vector2f(-300 * dt, 0));
			boss.wasMovingleft = 1;
			boss.wasMovingright = 0;
			karizmaBoss.restart();
		}

		if (boss.Boss.getPosition().x <= -128 && boss.wasMovingleft)
		{
			boss.isMovingleft = false;
			boss.Boss.move(0, 0);
			if (KarizmaTime.asSeconds() >= 5)
				boss.isMovingright = true;

		}
	}
}

//void SpaceInvader::PowerUps(float dt)
//{
//	for (int i = 0; i < NumOfEnemies; i++)
//	{
//		enemies[i].enemypower.powerTime = enemies[i].enemypower.powerclock.getElapsedTime();
//		if (enemies[i].sprite.getScale().x == 0)
//			enemies[i].enemypower.powerclock.restart();
//
//		enemies[i].enemypower.effect = rand() % 2000 + 1;
//
//		if (enemies[i].enemypower.powerTime.asMilliseconds() < 50 && enemies[i].enemypower.powerSpared == false)
//		{
//			enemies[i].enemypower.powerclock.restart();
//			enemies[i].enemypower.sprite.move(Vector2f(0, 900 * dt));
//			//live
//			if (enemies[i].enemypower.effect <= 1000)
//			{
//				enemies[i].enemypower.powerSpared = true;
//				enemies[i].enemypower.sprite.setFillColor(Color(125, 30, 125, 255));
//				if (enemies[i].enemypower.sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()) && enemies[i].enemypower.powerConsumed == false)
//				{
//					enemies[i].enemypower.powerConsumed = true;
//					player.health++;
//					enemies[i].enemypower.sprite.setFillColor(Color(0, 0, 0, 0));
//				}
//			}
//			//fire rate
//			if (enemies[i].enemypower.effect <= 2000 && enemies[i].enemypower.effect > 1000)
//			{
//
//				enemies[i].enemypower.powerSpared = true;
//				enemies[i].enemypower.sprite.setFillColor(Color(0, 255, 0, 255));
//				if (enemies[i].enemypower.sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()) && enemies[i].enemypower.powerConsumed == false)
//				{
//					enemies[i].enemypower.powerConsumed = true;
//					enemies[i].enemypower.sprite.setFillColor(Color(0, 0, 0, 0));
//					enemies[i].enemypower.fireRate = true;
//
//				}
//
//			}
//
//		}
//		//fireratecont
//		if (enemies[i].enemypower.powerTime.asSeconds() < 5 && enemies[i].enemypower.fireRate == true)
//		{
//			for (int j = 0; j < NumOfBullets; j++)
//			{
//				bullets[j].speed.y -= 100;
//			}
//		}
//		else if (enemies[i].enemypower.powerTime.asSeconds() >= 5)
//		{
//			for (int j = 0; j < NumOfBullets; j++)
//			{
//				bullets[j].speed.y = -900;
//				enemies[i].enemypower.fireRate = false;
//			}
//		}
//	}
//}