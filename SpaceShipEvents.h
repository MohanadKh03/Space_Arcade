// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

// Create a struct to hold every Shapceship action
struct myPlayer {
	string playerName;
	int score_BrickBreaker = 0;
	int score_2ndGame = 0;
	int score_SpaceInvader = 0;
};

void setTextureNSprite(Texture& te, Sprite& se, const float& scale, float xPos, float yPos) {
	se.setTexture(te);
	se.setScale(scale, scale);
	se.setPosition(xPos, yPos);
}

void ChangeSprite(Sprite& YP, float dt, int& x, int& y, float& spriteTimer, float& spriteDelay, int sizeX ,int sizeY) {
	if (spriteTimer <= 0) {
		x++;
		x %= 4;
		YP.setTextureRect(IntRect(x * sizeX, y * sizeY, sizeX, sizeY));
		spriteTimer = spriteDelay;
	}
	else {
		spriteTimer -= 1 * dt;
	}
}
bool collison = false;
bool canPlay = false;

Clock animationClock;
int animationCount = 0;

int* temp_ptr;
void Collision(Sprite& body, Sprite& player, View& camera, float speed, int& collisionID = *temp_ptr, int id = 0, bool GM = false)
{
	if (GM) {
		//FloatRect rect = FloatRect(player.getGlobalBounds().left, player.getGlobalBounds().top, player.getGlobalBounds().width + 40, player.getGlobalBounds().height + 40);
		FloatRect rect = FloatRect(body.getGlobalBounds().left - 50, body.getGlobalBounds().top - 50, body.getGlobalBounds().width + 100, body.getGlobalBounds().height + 100);
		Vector2f playerPos = { player.getPosition().x + (player.getGlobalBounds().width / 2), player.getPosition().y + (player.getGlobalBounds().height / 2) };
		if (rect.contains(playerPos)) {
			collison = true;
			canPlay = true;
			collisionID = id;
		}
	}
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

// Define the space ship struct
struct SpaceShip {
	// Define Textures
	Texture GameMachine;
	Texture GameMachine3;
	Texture bottomwall;
	Texture Bluescreen;
	Texture wall;
	Texture wall2;
	Texture wall4;
	Texture Background;
	Texture Player;
	Texture DialougeBox;
	Texture NPC1;

	// Define Sprites
	Sprite GM_Sprite;
	Sprite GM_Sprite2;
	Sprite GM_Sprite3;
	Sprite BottomWall_Sprite;
	Sprite BS1;
	Sprite wall1;
	Sprite wall3;
	Sprite wall5;
	Sprite Background_Sprite;
	Sprite YourPlayer;
	Sprite DB1;
	Sprite DB2;
	Sprite DB3;
	Sprite DB4;
	Sprite Alien1;

	// Define Texts
	Font Dialouge;
	Text test;
	Text AskUser;
	Text PlayGame1;
	Text PlayGame2;
	Text PlayGame3;
	Text LeaderBoard;

	int x = 0, y = 0; // For the sprite sheet

	int screenXBorders = 20;
	int screenYBorders = 100;
	float speed = 100.0f;
	bool gameCollision = false;

	float spriteDelay = 0.09f;
	float spriteTimer = 0.0f;

	// Define functions
	SpaceShip(RenderWindow&, int&, float&, View&, bool&);
	void Update(RenderWindow&, View&, float, int&);
	void Render(RenderWindow&, View&, int);
};

void SpaceShip::Update(RenderWindow& window, View& camera, float dt, int& collisionID) {
	speed = 500 * dt;
	if (Keyboard::isKeyPressed(Keyboard::Right) && YourPlayer.getPosition().x < window.getSize().x - (screenXBorders + 650))
	{
		YourPlayer.move(speed, 0);
		camera.move(speed, 0);
		y = 2;
		ChangeSprite(YourPlayer, dt, x, y, spriteTimer, spriteDelay, 64, 64);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && YourPlayer.getPosition().x > screenXBorders)
	{
		YourPlayer.move(-speed, 0);
		camera.move(-speed, 0);
		y = 1;
		ChangeSprite(YourPlayer, dt, x, y, spriteTimer, spriteDelay, 64, 64);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up) && YourPlayer.getPosition().y > screenYBorders)
	{
		YourPlayer.move(0, -speed);
		camera.move(0, -speed);
		y = 3;
		ChangeSprite(YourPlayer, dt, x, y, spriteTimer, spriteDelay, 64, 64);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && YourPlayer.getPosition().y < window.getSize().y - (screenYBorders + 300))
	{
		YourPlayer.move(0, speed);
		camera.move(0, speed);
		y = 0;
		ChangeSprite(YourPlayer, dt, x, y, spriteTimer, spriteDelay, 64, 64);
	}
	else {
		YourPlayer.setTextureRect(IntRect(0 * 64, y * 64, 64, 64));
	}
	int t = 4, l = 0;
	float a = 0.09f, b = 0;
	ChangeSprite(Alien1, dt, t, l, a, b, 32, 32);
	
	collisionID = 0;
	collison = false;

	Collision(GM_Sprite, YourPlayer, camera, speed, collisionID, 1, true);

	Collision(GM_Sprite2, YourPlayer, camera, speed, collisionID, 2, true);

	Collision(GM_Sprite3, YourPlayer, camera, speed, collisionID, 3, true);

	Collision(BS1, YourPlayer, camera, speed, collisionID, 4, true);

	Collision(wall1, YourPlayer, camera, speed);

	Collision(wall3, YourPlayer, camera, speed);

	Collision(wall5, YourPlayer, camera, speed);
	
	Render(window, camera, collisionID);
}

// Define the constructor of the space ship
SpaceShip::SpaceShip(RenderWindow& window, int& gameID, float& dt, View& camera, bool& spaceShip) {
	///// LAYERS
	
	GameMachine.loadFromFile("game machine.png");
	
	setTextureNSprite(GameMachine, GM_Sprite, 0.15f, 30, 80);
	setTextureNSprite(GameMachine, GM_Sprite2, 0.18f, 1040, 80);
	GM_Sprite2.setScale(-0.18f, 0.18f);
	GM_Sprite2.setColor(Color::Red);

	GameMachine3.loadFromFile("SpaceInvaderMachineFinal.png");
	
	// GM_Sprite3.setTexture(GameMachine3);
	setTextureNSprite(GameMachine3, GM_Sprite3, 0.18f, 40, 500);

	bottomwall.loadFromFile("bottomwall.jpg");
	
	setTextureNSprite(bottomwall, BottomWall_Sprite, 0.799f, 1046, 599.5);

	Bluescreen.loadFromFile("Bluescreen.jpg");
	
	setTextureNSprite(Bluescreen, BS1, 0.799f, 1110, 190);

	wall.loadFromFile("wall.jpg");
	
	setTextureNSprite(wall, wall1, 0.799f, 1040, 70);

	wall2.loadFromFile("wall2.jpg");
	
	setTextureNSprite(wall2, wall3, 0.799f, 1040, 520);

	wall4.loadFromFile("wall3.jpg");
	
	setTextureNSprite(wall4, wall5, 0.799f, 1040, 250);

	DialougeBox.loadFromFile("White box2.png");
	setTextureNSprite(DialougeBox, DB1, 3.5, 35, 70);
	setTextureNSprite(DialougeBox, DB2, 3.5, 1000, 40);
	setTextureNSprite(DialougeBox, DB3, 3.5, 40, 460);
	setTextureNSprite(DialougeBox, DB4, 3.5, 1120, 175);
	//END OF LAYERS
	Dialouge.loadFromFile("ARCADE_N.TTF");
	

	texts(PlayGame1, "Press 'Enter' to \nplay Brick Breaker", 40, 80, 8, Dialouge);
	PlayGame1.setFillColor(Color::Black);
	texts(PlayGame2, "Press 'Enter' to \nplay Duck", 1005, 50, 8, Dialouge);
	PlayGame2.setFillColor(Color::Black);
	texts(PlayGame3, "Press 'Enter' to \nplay Space Invader", 46, 470, 8, Dialouge);
	PlayGame3.setFillColor(Color::Black);
	texts(LeaderBoard, "Press 'Enter' to \nopen Leaderboard", 1125, 185, 9, Dialouge);
	LeaderBoard.setFillColor(Color::Black);

	// Background's Stuff
	
	Background.loadFromFile("Background2 Final.jpg");
	
	setTextureNSprite(Background, Background_Sprite, 0.8f, 0, 0);

	//Player's Stuff
	
	Player.loadFromFile("yellow hair boy.png");
	
	setTextureNSprite(Player, YourPlayer, 1, window.getSize().x / 2.f, window.getSize().y / 2.f);
	YourPlayer.setTextureRect(IntRect(0 * 64, 0 * 64, 64, 64));

	//NPCs' stuff
	NPC1.loadFromFile("Alien_idle.png");
	int l = 0;
	ChangeSprite(Alien1, dt, x, l, spriteTimer, spriteDelay, 32, 32);
	setTextureNSprite(NPC1, Alien1, 3.5, 900.0, 400.0);
	Alien1.setScale(-3.5, 3.5);
	Alien1.setTextureRect(IntRect(0 * 32, 0 * 32, 32, 32));
	
	
}

// Define the Render function of the space ship
void SpaceShip::Render(RenderWindow& window, View& camera, int collisionID) {
	window.draw(GM_Sprite);
	window.draw(wall5);
	window.draw(wall3);
	window.draw(wall1);
	window.draw(BS1);
	window.draw(Background_Sprite);
	window.draw(GM_Sprite2);
	window.draw(GM_Sprite3);
	window.setView(camera);
	window.draw(Alien1);
	window.draw(YourPlayer);
	window.draw(BottomWall_Sprite);
	
	if (collison) {
		switch (collisionID)
		{
		case 1:
			window.draw(DB1);
			window.draw(PlayGame1);
			break;
		case 2:
			window.draw(DB2);
			window.draw(PlayGame2);
			break;
		case 3:
			window.draw(DB3);
			window.draw(PlayGame3);
			break;
		case 4:
			window.draw(DB4);
			window.draw(LeaderBoard);
			break;
		}
	}
}


