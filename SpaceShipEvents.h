// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
void MovementSpaceShip(RenderWindow& window, View& camera,Sprite& YP,int& x,int& y/*, float dt*/) {
	Texture GM;
	GM.loadFromFile("game machine.png");
	Sprite GM1(GM);
	const float GMscale = 0.15f;
	GM1.setScale(GMscale, GMscale);
	GM1.setPosition(0, 0);

	int screenXBorders = 20;
	int screenYBorders = 100;
	const int speed = 25;
	if (Keyboard::isKeyPressed(Keyboard::Right) && YP.getPosition().x < window.getSize().x - screenXBorders)
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
	else if (Keyboard::isKeyPressed(Keyboard::Down) && YP.getPosition().y < window.getSize().y - screenYBorders)
	{
		YP.move(0, speed);
		camera.move(0,speed);
		x++;
		x %= 4;
		y = 0;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));

	}
	window.draw(GM1);
}
