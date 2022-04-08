// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
void MovementSpaceShip(RenderWindow& window, View& camera, Sprite& YP, int& x, int& y/*, float dt*/) {
	// layers
	Texture GM;
	GM.loadFromFile("game machine.png");
	Sprite GM1(GM);
	const float GMscale = 0.15f;
	GM1.setScale(GMscale, GMscale);
	GM1.setPosition(30, 80);
	Texture Bluescreen;
	Bluescreen.loadFromFile("Bluescreen.jpg");
	Sprite BS1(Bluescreen);
	const float BS1scale = 0.799f;
	BS1.setScale(BS1scale, BS1scale);
	BS1.setPosition(1100, 190);
	Texture wall;
	wall.loadFromFile("wall.jpg");
	Sprite wall1(wall);
	const float wallscale = 0.799f;
	wall1.setScale(wallscale, wallscale);
	wall1.setPosition(1040, 70);
	Texture wall2;
	wall2.loadFromFile("wall2.jpg");
	Sprite wall3(wall2);
	const float wall2scale = 0.799f;
	wall3.setScale(wall2scale, wall2scale);
	wall3.setPosition(1040, 520);
	Texture wall4;
	wall4.loadFromFile("wall3.jpg");
	Sprite wall5(wall4);
	const float wall3scale = 0.799f;
	wall5.setScale(wall3scale, wall3scale);
	wall5.setPosition(1040, 250);
//end of layers
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
