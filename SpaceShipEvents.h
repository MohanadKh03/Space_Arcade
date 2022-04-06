// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
void MovementSpaceShip(RenderWindow& window, View& camera,Sprite& YP,int& x,int& y) {
	Texture GM;
	GM.loadFromFile("game machine.png");
	Sprite GM1(GM);
	const float GMscale = 0.15;
	GM1.setScale(GMscale, GMscale);
	GM1.setPosition(0, 0);
	Texture box4;
	box4.loadFromFile("box3.png");
	Sprite box5(box4);
	const float box4scale = 1.2;
	box5.setScale(box4scale, box4scale);
	box5.setPosition(0, 0);
	Texture box2;
	box2.loadFromFile("box3.png");
	Sprite box3(box2);
	const float box2scale = 1.2;
	box3.setScale(box2scale, box2scale);
	box3.setPosition(0, 0);
	Texture box;
	box.loadFromFile("boxs2.png");
	Sprite box1(box);
	const float boxscale = 1.2;
	box1.setScale(boxscale, boxscale);
	box1.setPosition(0, 0);
	Texture box6;
	box6.loadFromFile("boxs2.png");
	Sprite box7(box6);
	const float box6scale = 1.2;
	box7.setScale(box6scale, box6scale);
	box7.setPosition(0, 0);
	int screenXRightBorders = 20;
	int screenXLeftBorders = 20;
	int screenYTopBorders = 100;
	int screenYBotBorders = 200;

	if (Keyboard::isKeyPressed(Keyboard::Right) && YP.getPosition().x < window.getSize().x - screenXBorders)
	{
		YP.move(10, 0);
		camera.move(10, 0);
		x++;
		x %= 4;
		y = 2;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && YP.getPosition().x > screenXBorders)
	{
		YP.move(-10, 0);
		camera.move(-10, 0);
		x++;
		x %= 4;
		y = 1;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up) && YP.getPosition().y > screenYTopBorders)
	{
		YP.move(0, -10);
		camera.move(0, -10);
		x++;
		x %= 4;
		y = 3;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && YP.getPosition().y < window.getSize().y - screenYBotBorders)
	{
		YP.move(0, 10);
		camera.move(0, 10);
		x++;
		x %= 4;
		y = 0;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));

	}
	
	if (box1.getGlobalBounds().intersects(YP.getGlobalBounds()) || box3.getGlobalBounds().intersects(YP.getGlobalBounds()) || box5.getGlobalBounds().intersects(YP.getGlobalBounds()) || box7.getGlobalBounds().intersects(YP.getGlobalBounds()) || GM1.getGlobalBounds().intersects(YP.getGlobalBounds()))
	{
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			YP.move(0,-0.1);
			camera.move(0, -0.1);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			YP.move(0, 0.1);
			camera.move(0, 0.1);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			YP.move(0.1, 0);
			camera.move(0.1, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			YP.move(-0.1, 0);
			camera.move(-0.1, 0);
		}
	}
	window.draw(GM1);
	window.draw(box1);
	window.draw(box3);
	window.draw(box5);
	window.draw(box7);
}
