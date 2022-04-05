// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
void MovementSpaceShip(RenderWindow& window, View& camera,Sprite& YP,int& x,int& y) {
	int screenXBorders = 20;
	int screenYBorders = 100;
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
	else if (Keyboard::isKeyPressed(Keyboard::Up) && YP.getPosition().y > screenYBorders)
	{
		YP.move(0, -10);
		camera.move(0, -10);
		x++;
		x %= 4;
		y = 3;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && YP.getPosition().y < window.getSize().y - screenYBorders)
	{
		YP.move(0, 10);
		camera.move(0, 10);
		x++;
		x %= 4;
		y = 0;
		YP.setTextureRect(IntRect(x * 64, y * 64, 64, 64));

	}
}
// the code that has bug 
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
using namespace sf;
int main() {
	int x = 0;
	int y = 0;
	RenderWindow window(sf::VideoMode(700, 700), "space arcade");
	Texture GM;
	GM.loadFromFile("game machine.png");
	Sprite GM1(GM);
	const float GMscale = 0.15;
	GM1.setScale(GMscale, GMscale);
	GM1.setPosition(-480, -250);
	Texture box4;
	box4.loadFromFile("box3.png");
	Sprite box5(box4);
	const float box4scale = 1.2;
	box5.setScale(box4scale, box4scale);
	box5.setPosition(-360, 80);
	Texture box2;
	box2.loadFromFile("box3.png");
	Sprite box3(box2);
	const float box2scale = 1.2;
	box3.setScale(box2scale, box2scale);
	box3.setPosition(-296, 40);
	Texture box;
	box.loadFromFile("boxs2.png");
	Sprite box1(box);
	const float boxscale = 1.2;
	box1.setScale(boxscale, boxscale);
	box1.setPosition(-215, 58);
	Texture box6;
	box6.loadFromFile("boxs2.png");
	Sprite box7(box6);
	const float box6scale = 1.2;
	box7.setScale(box6scale, box6scale);
	box7.setPosition(-356, -38);
	Texture YPt;
	Texture Bg;
	Bg.loadFromFile("back ground.jpeg");
	Sprite Bg1(Bg);
	const float Bgscale = 0.8;
	Bg1.setScale(Bgscale, Bgscale);
	Bg1.setPosition(-500, -300);
	YPt.loadFromFile("yellow hair boy.png");
	Sprite YP;
	View camera(sf::FloatRect(0, 0, 600, 600));
	camera.setCenter(YP.getPosition());
	YP.setTexture(YPt);
	YP.setTextureRect(IntRect(x * 64, 0 * 64, 64, 64));
	YP.setPosition(0, 0);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
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
		if (box1.getGlobalBounds().intersects(YP.getGlobalBounds()) || box3.getGlobalBounds().intersects(YP.getGlobalBounds()) || box5.getGlobalBounds().intersects(YP.getGlobalBounds()) || box7.getGlobalBounds().intersects(YP.getGlobalBounds()) || GM1.getGlobalBounds().intersects(YP.getGlobalBounds()))
		{
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				YP.move(0, -0.1);
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
		window.setView(camera);
		window.clear();
		window.draw(GM1);
		window.draw(box7);
		window.draw(box5);
		window.draw(box3);
		window.draw(box1);
		window.draw(Bg1);
		window.draw(YP);
		window.display();
	}

	return 0;
}