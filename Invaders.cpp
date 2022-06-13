#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Invaders.h"
using namespace std;

bool movingright = true;
bool movingleft = false;
bool BossMovingRight = true;
bool BoosMovingLeft = false;
float windowsizex = sf::VideoMode::getDesktopMode().width;
float windowsizey = sf::VideoMode::getDesktopMode().height;
int side = sf::VideoMode::getDesktopMode().width - 120;
int z = 0;

SpaceInvader::SpaceInvader(sf::RenderWindow& window) {

	//background music
	backgroundMusic.openFromFile("Sounds/Space-Invaders/Backtheme.wav");
	backgroundMusic.setLoop(true);
	//sheild stuff
	sheilds[0].body.setPosition(50, sf::VideoMode::getDesktopMode().height - sf::VideoMode::getDesktopMode().height / 4);

	for (int i = 0; i < 3; i++)
	{
		if (i > 0)
			sheilds[i].body.setPosition(sheilds[i - 1].body.getPosition().x + 700, sheilds[i - 1].body.getPosition().y);
		sheilds[i].texture.loadFromFile("Textures/Space Invaders/Shield.png");
		sheilds[i].body.setTexture(&sheilds[i].texture);
		sheilds[i].health = 100;
		sheilds[i].body.setSize(sf::Vector2f(400.f, 100.f));
		sheilds[i].active = true;

	}
	//show the score
	GameOverText.setPosition(sf::Vector2f(windowsizex / 2 - 80 * WindowFactor, windowsizey / 2));
	GameOverFont.loadFromFile("Fonts/ARCADE_R.ttf");
	GameOverText.setFont(GameOverFont);
	GameOverText.setFillColor(sf::Color(255, 0, 0));
	score = 0;
	scoretext.setPosition(sf::Vector2f(window.getSize().x - 300, 0));
	scoretext.setString("Score: " + to_string(score));
	scorefont.loadFromFile("Fonts/ARCADE_R.ttf");
	scoretext.setFont(scorefont);
	scoretext.setFillColor(sf::Color(0, 255, 0));
	livestext.setPosition(sf::Vector2f(window.getSize().x - 300, scoretext.getScale().y + 50));
	livestext.setString("Lives " + to_string(5));
	livesfont.loadFromFile("Fonts/ARCADE_R.ttf");
	livestext.setFont(livesfont);
	livestext.setFillColor(sf::Color(0, 255, 255));
	for (int i = 0; i < 3; i++)
	{
		SheildText[i].setPosition(sheilds[i].body.getPosition());
		SheildFont[i].loadFromFile("Fonts/ARCADE_R.ttf");
		SheildText[i].setFont(SheildFont[i]);
		SheildText[i].setFillColor(sf::Color(sf::Color::Red));
		SheildText[i].setString(to_string(sheilds[i].health)+ "%");
	}


	srand(time(0));

	//boss stuff
	/*boss.BossTexture.loadFromFile("Textures/Space Invaders/enemyBlack.png");
	boss.Boss.setTexture(boss.BossTexture);
	boss.Boss.setScale(sf::Vector2f(2, 3));
	boss.Boss.setPosition(sf::Vector2f(-boss.Boss.getScale().x, 0));

	boss.Boss.setColor(sf::Color(0, 255, 255, 0));*/

	//background
	background.loadFromFile("Textures/Space Invaders/Space Invaders Background.png");
	backgroundsprite.setTexture(background);
	//Enemy Stuff
	enemies[0].health = 100;
	enemies[0].posx = 20;
	enemies[0].posy = 0;
	enemies[0].enemytexture.loadFromFile("Textures/Space Invaders/enemyBlack.png");
	enemies[0].enemy.setTexture(enemies[0].enemytexture);
	enemies[0].enemy.setScale(sf::Vector2f(0.8 * WindowFactor, 0.8 * WindowFactor));
	enemies[0].enemyshot.loadFromFile("Sounds/Space-Invaders/EnemyShot.wav");
	enemies[0].enemysound.setBuffer(enemies[0].enemyshot);
	enemies[0].enemy.setPosition(sf::Vector2f(enemies[0].posx, enemies[0].posy));
	enemies[0].enemy.setColor(sf::Color(enemies[0].enemy.getColor().r, enemies[0].enemy.getColor().b, enemies[0].enemy.getColor().g, 240));
	enemies[0].enemybu.body.setFillColor(sf::Color(0, 255, 0, 0));
	enemies[0].enemybu.body.setSize(sf::Vector2f(10.f, 20.f));
	enemies[0].enemybu.body.setPosition(enemies[0].enemy.getPosition().x + 46.5, enemies[0].enemy.getPosition().y + 42);
	/*enemies[0].enemypower.body.setRadius(3.f);
	enemies[0].enemypower.body.setPosition(enemies[0].enemy.getPosition());
	enemies[0].enemypower.body.setFillColor(sf::Color(0, 255, 255, 0));
	enemies[0].enemypower.powerConsumed = false;
	enemies[0].enemypower.fireRate == false;*/
	for (int i = 1; i < NumOfEnemies; i++)
	{

		enemies[i].health = 100;
		enemies[i].enemytexture.loadFromFile("Textures/Space Invaders/enemyBlack.png");
		enemies[i].enemy.setTexture(enemies[i].enemytexture);;
		enemies[i].enemy.setScale(sf::Vector2f(0.8 * WindowFactor, 0.8 * WindowFactor));
		enemies[i].enemyshot.loadFromFile("Sounds/Space-Invaders/EnemyShot.wav");
		enemies[i].enemysound.setBuffer(enemies[i].enemyshot);
		enemies[i].enemybu.body.setFillColor(sf::Color(0, 255, 0, 0));
		enemies[i].enemybu.body.setSize(sf::Vector2f(4.f, 8.f));
		enemies[i].enemybu.released = false;
		enemies[i].enemybu.body.setPosition(enemies[i].enemy.getPosition().x + 46.5, enemies[i].enemy.getPosition().y + 42);
		enemies[i].enemybu.body.setScale(sf::Vector2f(2.f, 4.f));
		/*enemies[i].enemypower.body.setRadius(3.f);
		enemies[i].enemypower.body.setPosition(enemies[i].enemy.getPosition());
		enemies[i].enemypower.body.setFillColor(sf::Color(0, 255, 255, 0));
		enemies[i].enemypower.powerConsumed = false;
		enemies[i].enemypower.fireRate == false;*/
		if (  i % 10 != 0)
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
	player.posy = sf::VideoMode::getDesktopMode().height - 100 * WindowFactor;
	player.playertexture.loadFromFile("Textures/Space Invaders/blueship.png");
	player.playershot.loadFromFile("Sounds/Space-Invaders/PlayerShot.wav");
	player.playersound.setBuffer(player.playershot);
	player.playersprite.setTexture(&player.playertexture);
	player.playersprite.setSize(sf::Vector2f(window.getSize().x / 21.68f, window.getSize().y / 14));
	player.playersprite.setPosition(sf::Vector2f(player.posx, player.posy));
	player.health = 5;
	//Bullets stuff
	for (int i = 0; i < NumOfBullets; i++)
	{
		bullets[i].released = false;
		bullets[i].body.setScale(sf::Vector2f(2.f, 4.f));
		bullets[i].body.setPosition(player.posx, player.posy);

	}
	//// Reset the score
	//score = 0;
	backgroundMusic.play();
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(100.f);

}

void SpaceInvader::EnemyMovement(float dt, sf::Clock& clock, sf::Time& deltatimemove)
{
	//setting the x,y positions for the already set in the constructor ones
	deltatimemove = clock.getElapsedTime();

	for (int i = 0; i < NumOfEnemies; i++)
	{
		if (enemies[i].enemybu.released == false)
			enemies[i].enemybu.body.setPosition(enemies[i].posx + 46.5, enemies[i].posy + 38);
		/*if (enemies[i].enemypower.powerSpared == false)
			enemies[i].enemypower.body.setPosition(enemies[i].enemy.getPosition());*/
		 
		enemies[i].posx = enemies[i].enemy.getPosition().x;
		enemies[i].posy = enemies[i].enemy.getPosition().y;


	}


	//containing the enemies and moving them right/left and down if they reach the far end(right/left)
	//the down statement with right and left booleans
	if (enemies[0].posx <= 20 && movingleft)
	{
		for (int i = 0; i < NumOfEnemies; i++)
			enemies[i].enemy.setPosition(sf::Vector2f(enemies[i].posx, enemies[i].posy + 60));
		movingright = true;
		movingleft = false;
	}
	if (enemies[NumOfEnemies - 1].posx >= side && movingright)
	{
		for (int i = 0; i < NumOfEnemies; i++)
			enemies[i].enemy.setPosition(sf::Vector2f(enemies[i].posx, enemies[i].posy + 60));
		movingright = false;
		movingleft = true;
	}


	//the right/left statements 
	if (movingleft && deltatimemove.asMilliseconds() >= 500)
	{
		for (int i = 0; i < NumOfEnemies; i++)
		{
			enemies[i].enemy.setPosition(sf::Vector2f(enemies[i].posx - 30, enemies[i].posy));
		}
		clock.restart();
	}
	else if (movingright && deltatimemove.asMilliseconds() >= 500)
	{
		for (int i = 0; i < NumOfEnemies; i++)
			enemies[i].enemy.setPosition(sf::Vector2f(enemies[i].posx + 30, enemies[i].posy));
		clock.restart();
	}

}

void SpaceInvader::PlayerMovement() {
	//setting the position of the player and containing between the borders .. also its movement
	player.posx = player.playersprite.getPosition().x;


	//stop player from getting out of screen
	if (sf::Mouse::getPosition().x > windowsizex - player.playersprite.getGlobalBounds().width)
		sf::Mouse::setPosition(sf::Vector2i(int(windowsizex - player.playersprite.getGlobalBounds().width), 0));


	player.playersprite.setPosition(sf::Vector2f(sf::Mouse::getPosition().x, player.posy));
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
	else
	{
		bulletDelay = 0;
	}
}

void SpaceInvader::ShootBullet(float& dt) {
	//moving the bullet FROM the player UPWARDS after it is shot
	bullets[bulletIndex].released = true;
	player.playersound.play();
	bullets[bulletIndex].body.setSize(sf::Vector2f(20.f, 40.f));
	bullets[bulletIndex].body.setPosition(player.playersprite.getPosition() + sf::Vector2f(player.playersprite.getSize().x / 2 - 2, 0));
	bullets[bulletIndex].speed = sf::Vector2f(0, -900);
	bulletIndex++;
}

void SpaceInvader::Collision(sf::RenderWindow& w, int& gameID) {
	//checking if the bullet hit the enemy or not (By going through all the bullets and all the enemies)
	for (int i = 0; i < NumOfEnemies; i++)
	{
		if (enemies[i].enemybu.body.getGlobalBounds().intersects(player.playersprite.getGlobalBounds()))
		{
			player.Damaged = true;
			--player.health;
			enemies[i].enemybu.released = false;
			enemies[i].enemybu.body.setFillColor(sf::Color(0, 255, 0, 0));
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
			if (bullets[i].body.getGlobalBounds().intersects(enemies[j].enemy.getGlobalBounds()))
			{
				enemies[j].health -= 20;
				enemies[j].enemy.setColor(sf::Color(enemies[j].red, enemies[j].enemy.getColor().g - 63, enemies[j].enemy.getColor().b - 63, enemies[j].enemy.getColor().a - 30));
				bullets[i].released = false;
				if (enemies[j].health <= 0)
				{
					enemies[j].enemy.setScale(sf::Vector2f(0.f, 0.f));
					score++;
					scoretext.setString("Score: " + to_string(score));
				}
				// Complete sprite change 	
			}

		}
		for (int j = 0; j < 3; j++)
		{
			if (bullets[i].body.getGlobalBounds().intersects(sheilds[j].body.getGlobalBounds()) && sheilds[j].active)
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
			if (enemies[i].enemy.getGlobalBounds().intersects(sheilds[j].body.getGlobalBounds()))
				sheilds[j].health = 0;


			if (enemies[i].enemybu.body.getGlobalBounds().intersects(sheilds[j].body.getGlobalBounds()) && sheilds[j].active)
			{
				sheilds[j].health--;
				SheildText[j].setString(to_string(sheilds[j].health) + "%");
				enemies[i].enemybu.body.setFillColor(sf::Color(0, 255, 0, 0));
				enemies[i].enemybu.released = false;
			}

		}
	}
	//checking if the enemy hits the player or if the score is max(All enemies are hit)



}

void SpaceInvader::Run(sf::RenderWindow& win, int& GAMEscore, sf::Event& e, float& dt, int& gameID) {
	GAMEscore = score;
	// win.draw(boss.Boss);
	win.draw(backgroundsprite);
	for (int i = 0; i < NumOfEnemies; i++) {

		win.draw(enemies[i].enemybu.body);
		win.draw(enemies[i].enemy);
		// win.draw(enemies[i].enemypower.body);
	}
	for (int i = 0; i < NumOfBullets; i++) {
		bullets[i].Update(dt);
		win.draw(bullets[i].body);
	}
	for (int i = 0; i < 3; i++)
	{
		win.draw(sheilds[i].body);
		win.draw(SheildText[i]);
	}
	if (SpaceInvader::isgameover == false)
	{

		win.draw(player.playersprite);
		win.draw(scoretext);
		win.draw(livestext);
		bulletsFunction(e, dt);
		Collision(win, gameID);
		EnemyMovement(dt, clock, deltatimemove);
		PlayerMovement();
		Destroyandgen(dt);
		/*Boss();
		Bossmovement(karizmaBoss, KarizmaTime, dt);*/
		Sheild();
		/*PowerUps(dt);*/
	}
	GameOver(win, gameID);
}

void Bullet::Update(float& dt) {
	if (!released) {
		body.setSize(sf::Vector2f(0, 0));
	}
	else {
		body.setSize(sf::Vector2f(2.f, 4.f));
	}
	body.move(speed * dt);
}

void SpaceInvader::GameOver(sf::RenderWindow& w, int& gameID)
{
	for (int i = 0; i < NumOfEnemies; i++)
	{
		if (enemies[i].enemy.getScale().x != 0 && enemies[i].enemy.getScale().y != 0)
		{
			if (enemies[i].enemy.getGlobalBounds().intersects(player.playersprite.getGlobalBounds()) || isgameover || player.health <= 0)
			{
				isgameover = true;
				GameOverText.setString("Game over \n Score :" + to_string(score) + "\n press Space to return");
				player.health = 100;
				w.clear();
				w.draw(GameOverText);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					gameID = 0;
			}
		}
	}
	if (score == NumOfEnemies) {
		isgameover = true;
		GameOverText.setString("level won \n your new score :" + to_string(score) + "\npress space to return");
		w.clear();
		w.draw(GameOverText);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			gameID = 0;
	}
	//cheats
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		score = NumOfEnemies;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		isgameover = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		score += 10;

}

void SpaceInvader::Destroyandgen(float dt)
{
	for (int i = 0; i < NumOfEnemies; i++)
	{
		if (enemies[i].enemy.getScale().x == 0 && !(enemies[i].enemybu.released))
			enemies[i].enemybu.body.setSize(sf::Vector2f(0, 0));
		if (enemies[i].enemy.getScale().x == 0 && !(enemies[i].enemybu.released))
			continue;
		bool lineshot;
		int linebegin = (i / 10) * 10;
		int bulletspeedgen = rand() % 11 + 2;
		for (int j = linebegin; j <= (linebegin + 11); j++)
		{

			if (enemies[j].enemy.getScale().x == 0 && !(enemies[i].enemybu.released))
				continue;
			if (enemies[j].enemybu.released)
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

				enemies[i].enemybu.released = true;
				enemies[i].bulletspeed = bulletspeedgen * 100;
				enemies[i].enemysound.play();

			}
		}
		if (enemies[i].enemybu.released == true)
		{
			enemies[i].enemybu.body.move(0, enemies[i].bulletspeed * dt);
			enemies[i].enemybu.body.setFillColor(sf::Color(0, 255, 0, 255));
		}
		//regen
		if (enemies[i].enemybu.body.getPosition().y > sf::VideoMode::getDesktopMode().height - 20)
		{
			enemies[i].enemybu.body.setFillColor(sf::Color(0, 255, 0, 0));
			enemies[i].enemybu.released = false;

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
			sheilds[i].body.setFillColor(sf::Color(0, 0, 0, 0));
			sheilds[i].active = false;
			SheildText[i].setScale(sf::Vector2f(0, 0));
			
		}
	}
}

//void SpaceInvader::Boss()
//{
//	if (score >= 20)
//	{
//		boss.Boss.setColor(sf::Color(0, 255, 255, 255));
//	}
//}
//void SpaceInvader::Bossmovement(sf::Clock& karizmaBoss, sf::Time& karizmatime, float dt)
//{
//	KarizmaTime = karizmaBoss.getElapsedTime();
//
//	if (boss.Boss.getColor().a)
//	{
//		if ((boss.Boss.getPosition().x >= side + boss.Boss.getScale().x && BossMovingRight) || (boss.Boss.getPosition().x <= -boss.Boss.getScale().x && BoosMovingLeft))
//		{
//			boss.Boss.move(sf::Vector2f(0, 0));
//			karizmaBoss.restart();
//		}
//
//		if (BoosMovingLeft == true && KarizmaTime.asSeconds() == 5) {
//			boss.Boss.move(sf::Vector2f(-2 * dt, 0));
//			BoosMovingLeft = false;
//			BossMovingRight = true;
//		}
//		if (BossMovingRight && KarizmaTime.asSeconds() == 5)
//		{
//			boss.Boss.move(sf::Vector2f(2 * dt, 0));
//			BoosMovingLeft = true;
//			BossMovingRight = false;
//		}
//
//	}
//}

//void SpaceInvader::PowerUps(float dt)
//{
//	for (int i = 0; i < NumOfEnemies; i++)
//	{
//		enemies[i].enemypower.powerTime = enemies[i].enemypower.powerclock.getElapsedTime();
//		if (enemies[i].enemy.getScale().x == 0)
//			enemies[i].enemypower.powerclock.restart();
//
//		enemies[i].enemypower.effect = rand() % 2000 + 1;
//
//		if (enemies[i].enemypower.powerTime.asMilliseconds() < 50 && enemies[i].enemypower.powerSpared == false)
//		{
//			enemies[i].enemypower.powerclock.restart();
//			enemies[i].enemypower.body.move(sf::Vector2f(0, 900 * dt));
//			//live
//			if (enemies[i].enemypower.effect <= 1000)
//			{
//				enemies[i].enemypower.powerSpared = true;
//				enemies[i].enemypower.body.setFillColor(sf::Color(125, 30, 125, 255));
//				if (enemies[i].enemypower.body.getGlobalBounds().intersects(player.playersprite.getGlobalBounds()) && enemies[i].enemypower.powerConsumed == false)
//				{
//					enemies[i].enemypower.powerConsumed = true;
//					player.health++;
//					enemies[i].enemypower.body.setFillColor(sf::Color(0, 0, 0, 0));
//				}
//			}
//			//fire rate
//			if (enemies[i].enemypower.effect <= 2000 && enemies[i].enemypower.effect > 1000)
//			{
//
//				enemies[i].enemypower.powerSpared = true;
//				enemies[i].enemypower.body.setFillColor(sf::Color(0, 255, 0, 255));
//				if (enemies[i].enemypower.body.getGlobalBounds().intersects(player.playersprite.getGlobalBounds()) && enemies[i].enemypower.powerConsumed == false)
//				{
//					enemies[i].enemypower.powerConsumed = true;
//					enemies[i].enemypower.body.setFillColor(sf::Color(0, 0, 0, 0));
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