// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

void ChangeSprite(Sprite& YP, float dt, int& x, int& y, float& spriteTimer, float& spriteDelay) {
	if (spriteTimer <= 0) {
		x++;
		x %= 4;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
		spriteTimer = spriteDelay;
	}
	else {
		spriteTimer -= 1 * dt;
	}
}

void Intersection(Sprite& body, Sprite& player, View& camera, int speed)
{
	if (body.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.move(0, speed);
			camera.move(0, speed);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.move(0, -speed);
			camera.move(0, -speed);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.move(-speed, 0);
			camera.move(-speed, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.move(speed, 0);
			camera.move(speed, 0);
		}
	}
}

Text AskUser;
void MovementSpaceShip(RenderWindow& window, View& camera, Sprite& YP, int& x, int& y, Sprite& GM1, Sprite& GM2, Sprite& GM3, Sprite& BS1, Sprite& wall1, Sprite& wall3, Sprite& wall5,int& gameID, float dt, float& spriteTimer, float spriteDelay) {
	int screenXBorders = 20;
	int screenYBorders = 100;
	int speed = 500 * dt;
	bool gameCollision = false;
	////

	////
	if (Keyboard::isKeyPressed(Keyboard::Right) && YP.getPosition().x < window.getSize().x - (screenXBorders + 650))
	{
		YP.move(speed, 0);
		camera.move(speed, 0);
		y = 2;
		ChangeSprite(YP, dt, x, y, spriteTimer, spriteDelay);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && YP.getPosition().x > screenXBorders)
	{
		YP.move(-speed, 0);
		camera.move(-speed, 0);
		y = 1;
		ChangeSprite(YP, dt, x, y, spriteTimer, spriteDelay);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up) && YP.getPosition().y > screenYBorders)
	{
		YP.move(0, -speed);
		camera.move(0, -speed);
		y = 3;
		ChangeSprite(YP, dt, x, y, spriteTimer, spriteDelay);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && YP.getPosition().y < window.getSize().y - (screenYBorders + 300))
	{
		YP.move(0, speed);
		camera.move(0, speed);
		y = 0;
		ChangeSprite(YP, dt, x, y, spriteTimer, spriteDelay);
	}

	Intersection(GM1, YP, camera, speed);
	
	Intersection(GM2, YP, camera, speed);
	
	Intersection(GM3, YP, camera, speed);

	Intersection(BS1, YP, camera, speed);
	
	Intersection(wall1, YP, camera, speed);
	
	Intersection(wall3, YP, camera, speed);
	
	Intersection(wall5, YP, camera, speed);
	
}


