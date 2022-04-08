// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
void MovementSpaceShip(RenderWindow& window, View& camera, Sprite& YP, int& x, int& y, Sprite GM1, Sprite BS1, Sprite wall1, Sprite wall3, Sprite wall5) {
	int screenXBorders = 20;
	int screenYBorders = 100;
	const int speed = 15;
	if (Keyboard::isKeyPressed(Keyboard::Right) && YP.getPosition().x < window.getSize().x - (screenXBorders + 650))
	{
		YP.move(speed, 0);
		camera.move(speed, 0);
		x++;
		x %= 4;
		y = 2;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && YP.getPosition().x > screenXBorders)
	{
		YP.move(-speed, 0);
		camera.move(-speed, 0);
		x++;
		x %= 4;
		y = 1;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up) && YP.getPosition().y > screenYBorders)
	{
		YP.move(0, -speed);
		camera.move(0, -speed);
		x++;
		x %= 4;
		y = 3;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && YP.getPosition().y < window.getSize().y - (screenYBorders + 300))
	{
		YP.move(0, speed);
		camera.move(0, speed);
		x++;
		x %= 4;
		y = 0;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));

	}
	
	if (GM1.getGlobalBounds().intersects(YP.getGlobalBounds())) {
		if (Keyboard::isKeyPressed(Keyboard::Up)){
			YP.move(0, speed);
				camera.move(0, speed);
				
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			YP.move(speed, 0);
				camera.move(speed, 0);
		}
}
	if (BS1.getGlobalBounds().intersects(YP.getGlobalBounds())) {
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			YP.move(0, speed);
			camera.move(0, speed);

		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			YP.move(-speed, 0);
			camera.move(-speed, 0);
		}
	}
	if (wall1.getGlobalBounds().intersects(YP.getGlobalBounds())) {
		 if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			YP.move(-speed, 0);
			camera.move(-speed, 0);
		}
	}
	if (wall3.getGlobalBounds().intersects(YP.getGlobalBounds())) {
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			YP.move(-speed, 0);
			camera.move(-speed, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			YP.move(speed, 0);
			camera.move(speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			YP.move(0, -speed);
			camera.move(0, -speed);

		}
	}
	if (wall5.getGlobalBounds().intersects(YP.getGlobalBounds())) {
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			YP.move(-speed, 0);
			camera.move(-speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			YP.move(speed, 0);
			camera.move(speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			YP.move(0, speed);
			camera.move(0, speed);

		}
	}
}
