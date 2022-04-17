// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>



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

/**
int ChoiceOfUser(string game, bool& gameCollision, int gameID) {
	if (gameCollision) {
		Text AskUser;
		Font font;
		font.loadFromFile("ARCADE_R.ttf");
		texts(AskUser, "Press y to play " + game, 50, 50, 30, font);
		if (Keyboard::isKeyPressed(Keyboard::Y))
			gameID = (game == "BrickBreaker" ? 1 : (game == "SpaceShooter" ? 2 : game == "SpaceInvader" ? 3 : 0));
	}
	return gameID;
}
**/
Text AskUser;
void MovementSpaceShip(RenderWindow& window, View& camera, Sprite& YP, int& x, int& y, Sprite& GM1, Sprite& GM2, Sprite& GM3, Sprite& BS1, Sprite& wall1, Sprite& wall3, Sprite& wall5,int& gameID) {
	int screenXBorders = 20;
	int screenYBorders = 100;
	const int speed = 9;
	bool gameCollision = false;
	////

	

	////
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

	Intersection(GM1, YP, camera, speed);
	
	Intersection(GM2, YP, camera, speed);
	
	Intersection(GM3, YP, camera, speed);

	Intersection(BS1, YP, camera, speed);
	
	Intersection(wall1, YP, camera, speed);
	
	Intersection(wall3, YP, camera, speed);
	
	Intersection(wall5, YP, camera, speed);
	
}


