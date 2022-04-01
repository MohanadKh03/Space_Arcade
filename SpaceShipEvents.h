// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
void MovementSpaceShip(View& camera,Sprite& YP,int& x,int& y) {
	if (Keyboard::isKeyPressed(Keyboard::Right) && YP.getPosition().x < 320)
	{
		YP.move(0.1, 0);
		camera.move(0.1, 0);
		x++;
		x %= 4;
		y = 2;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && YP.getPosition().x > -470)
	{
		YP.move(-0.1, 0);
		camera.move(-0.1, 0);
		x++;
		x %= 4;
		y = 1;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up) && YP.getPosition().y > -230)
	{
		YP.move(0, -0.1);
		camera.move(0, -0.1);
		x++;
		x %= 4;
		y = 3;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && YP.getPosition().y < 270)
	{
		YP.move(0, 0.1);
		camera.move(0, 0.1);
		x++;
		x %= 4;
		y = 0;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));

	}
}