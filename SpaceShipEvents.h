// ms2k lzez
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>


void setTextureNSprite(Texture& te, Sprite& se, const float& scale, float xPos, float yPos) {
	se.setTexture(te);
	se.setScale(scale, scale);
	se.setPosition(xPos, yPos);
}

void ChangeSprite(Sprite& YP, float dt, int& x, int& y, float& spriteTimer, float& spriteDelay, int sizeX, int sizeY, int spriteWidth) {
	if (spriteTimer <= 0) {
		x++;
		x %= spriteWidth;
		YP.setTextureRect(IntRect(x * sizeX, y * sizeY, sizeX, sizeY));
		spriteTimer = spriteDelay;
	}
	else {
		spriteTimer -= 1 * dt;
	}
}
bool collison = false;
bool canPlay = false;

int npcID;
bool NPC = false;
int* npcCollisionID;

Clock animationClock;
int animationCount = 0;

int l = 0;
int n = 0;
float alienSpriteDelay = 0.15f;
float alienSpriteTimer = 0.0f;

// SpriteSheet variables
int g = 0, h = 0;

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
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.move(0, -speed);
			camera.move(0, -speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.move(-speed, 0);
			camera.move(-speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.move(speed, 0);
			camera.move(speed, 0);
		}
	}
}

// Define the space ship struct
struct SpaceShip {
	// Define Textures
	Texture BackScreen;
	Texture GameMachine;
	Texture GameMachine3;
	Texture GameMachinePurp;
	Texture GameMachineSpace;
	Texture GameMachineRow1;
	Texture GameMachineRow2;
	Texture GameMachineRow3;
	Texture bottomwall;
	Texture Bluescreen;
	Texture wall;
	Texture wall2;
	Texture wall4;
	Texture Background;
	Texture Player;
	Texture DialougeBox;
	Texture VendingMachine;
	Texture NPC1;
	Texture NPC2;
	Texture NPC3;
	Texture NPC4;
	Texture NPC5;
	Texture NPC6;
	Texture NPC7;
	Texture NPC8;
	Texture NPC9;

	// Define Sprites
	Sprite BackS;
	Sprite GM_Sprite;
	Sprite GM_Sprite2;
	Sprite GM_Sprite3;
	Sprite GM_Sprite4;
	Sprite GM_Sprite5;
	Sprite GM_Row1;
	Sprite GM_Row2;
	Sprite GM_Row3;
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
	Sprite DBA;
	Sprite DBB;
	Sprite DBC;
	Sprite DBD;
	Sprite DBE;
	Sprite DBF;
	Sprite VM;
	Sprite Alien1;
	Sprite HellBoy;
	Sprite Nurse;
	Sprite Elf;
	Sprite C3PO;
	Sprite R4D4;
	Sprite Todo;
	Sprite Solilas;
	Sprite Lisa;

	// Define Texts
	Font Dialouge;
	Font Dialouge2;
	Font Dialouge3;

	Text test;
	Text AskUser;
	Text PlayGame1;
	Text PlayGame2;
	Text PlayGame3;
	Text LeaderBoard;
	Text Speech1;
	Text Speech2;
	Text Speech3;
	Text Speech4;
	Text Speech5;
	Text Speech6;

	int x = 0, y = 0; // For the sprite sheet

	float speed = 100.0f;
	bool gameCollision = false;

	float spriteDelay = 0.09f;
	float spriteTimer = 0.0f;

	// Define functions
	SpaceShip(RenderWindow&, int&, float&, View&);
	void Update(RenderWindow&, View&, float, int&);
	void Render(RenderWindow&, View&, int);
};

// Define the constructor of the space ship
SpaceShip::SpaceShip(RenderWindow& window, int& gameID, float& dt, View& camera) {
	///// LAYERS
	BackScreen.loadFromFile("Textures/Main/bcg1@2x.png");
	setTextureNSprite(BackScreen, BackS, 1, -500, -400);

	GameMachine.loadFromFile("Textures/Main/game machine.png");

	setTextureNSprite(GameMachine, GM_Sprite, 0.15f, 30, 80);
	setTextureNSprite(GameMachine, GM_Sprite2, 0.18f, 1040, 80);
	GM_Sprite2.setScale(-0.18f, 0.18f);
	GM_Sprite2.setColor(Color::Red);


	GameMachinePurp.loadFromFile("Textures/Main/GameMachinePurp2 02.png");
	setTextureNSprite(GameMachinePurp, GM_Sprite4, 0.09f, 220, 70);

	GameMachineSpace.loadFromFile("Textures/Main/DuckMachine.png");
	setTextureNSprite(GameMachineSpace, GM_Sprite5, 0.1f, 370, 300);

	GameMachineRow1.loadFromFile("Textures/Main/Sample 1.png");
	setTextureNSprite(GameMachineRow1, GM_Row1, 0.1f, 50, 300);

	GameMachineRow2.loadFromFile("Textures/Main/Sample 2.png");
	setTextureNSprite(GameMachineRow2, GM_Row2, 0.1f, 50, 500);

	bottomwall.loadFromFile("Textures/Main/bottomwall.jpg");
	setTextureNSprite(bottomwall, BottomWall_Sprite, 0.799f, 1046, 599.5);

	Bluescreen.loadFromFile("Textures/Main/Bluescreen.jpg");
	setTextureNSprite(Bluescreen, BS1, 0.799f, 1110, 190);

	wall.loadFromFile("Textures/Main/wall.jpg");
	setTextureNSprite(wall, wall1, 0.799f, 1040, 70);

	wall2.loadFromFile("Textures/Main/wall2.jpg");
	setTextureNSprite(wall2, wall3, 0.799f, 1040, 520);

	wall4.loadFromFile("Textures/Main/wall3.jpg");
	setTextureNSprite(wall4, wall5, 0.799f, 1040, 250);

	DialougeBox.loadFromFile("Textures/Main/White box2.png");
	setTextureNSprite(DialougeBox, DB1, 3.5, 35, 70);
	setTextureNSprite(DialougeBox, DB2, 3.5, 375, 250);
	setTextureNSprite(DialougeBox, DB3, 3.5, 225, 25);
	setTextureNSprite(DialougeBox, DB4, 3.5, 1120, 185);
	setTextureNSprite(DialougeBox, DBA, 3.7, 955, 190);
	setTextureNSprite(DialougeBox, DBB, 3.0, 325, 585);
	setTextureNSprite(DialougeBox, DBC, 4.0, 475, 5);
	DBC.setScale(4.5, 4.0);
	setTextureNSprite(DialougeBox, DBD, 4.0, 1280, 240);
	DBD.setScale(6.2, 4.0);
	setTextureNSprite(DialougeBox, DBE, 4.0, 60, 250);
	setTextureNSprite(DialougeBox, DBF, 3.5, 1015, 55);

	//END OF LAYERS
	Dialouge.loadFromFile("Fonts/ARCADE_N.TTF");
	Dialouge2.loadFromFile("Fonts/Syakifah_Personal_Use.OTF");
	Dialouge3.loadFromFile("Fonts/World-of-spell.TTF");

	texts(PlayGame1, "Press 'Enter' to \nplay Brick Breaker", 40, 80, 8, Dialouge);
	PlayGame1.setFillColor(Color::Black);
	texts(PlayGame2, "Press 'Enter' to \nplay Duck", 380, 260, 8, Dialouge);
	PlayGame2.setFillColor(Color::Black);
	texts(PlayGame3, "Press 'Enter' to \nplay Space Invader", 230, 35, 8, Dialouge);
	PlayGame3.setFillColor(Color::Black);
	texts(LeaderBoard, "Press 'Enter' to \nopen Leaderboard", 1125, 195, 9, Dialouge);
	LeaderBoard.setFillColor(Color::Black);
	texts(Speech1, "vilis irrumator praetor", 960, 195, 18, Dialouge2);
	Speech1.setFillColor(Color::Red);
	texts(Speech2, "I'm too short\nI can't reach it :(", 333, 588, 15, Dialouge3);
	Speech2.setFillColor(Color::Blue);
	texts(Speech3, "This Cola sucks!\n would not try it if I were you", 485, 10, 15, Dialouge2);
	//Speech3.setFillColor(Color::Black);
	texts(Speech4, "I can not find my name on the leaderboard\nGod! All my progress is lost!", 1290, 250, 15, Dialouge2);

	texts(Speech5, "I am having so much fun!\n This place is great", 70, 260, 15, Dialouge2);

	texts(Speech6, "No Game,\nI am sleeping", 1025, 65, 9, Dialouge);
	Speech6.setFillColor(Color::Black);
	// Background's Stuff

	Background.loadFromFile("Textures/Main/BackgroundCut.png");
	setTextureNSprite(Background, Background_Sprite, 0.8f, 0, 0);
	//

	//Other's

	VendingMachine.loadFromFile("Textures/Main/Full Vending Machine 02.png");
	setTextureNSprite(VendingMachine, VM, 2, 550, 70);

	//Player's Stuff

	Player.loadFromFile("Textures/Characters/yellow hair boy.png");
	setTextureNSprite(Player, YourPlayer, 1, window.getSize().x / 2.f, window.getSize().y / 2.f - 30.f);
	YourPlayer.setTextureRect(IntRect(0 * 64, 0 * 64, 64, 64));

	//NPCs' stuff
	NPC1.loadFromFile("Textures/Characters/Alien_idle 02.png");
	setTextureNSprite(NPC1, Alien1, 3.5, 1010.0, 280.0);
	Alien1.setScale(-3.5, 3.5);

	NPC2.loadFromFile("Textures/Characters/HellBoy 02.png");
	setTextureNSprite(NPC2, HellBoy, 3.5, 700, 65);
	//HellBoy.setScale(-0.12, 0.12);

	NPC3.loadFromFile("Textures/Characters/Nurse-cut.png");
	setTextureNSprite(NPC3, Nurse, 1, 830, 115);

	NPC4.loadFromFile("Textures/Characters/Elf.png");
	setTextureNSprite(NPC4, Elf, 1.5, 75, 315);

	NPC5.loadFromFile("Textures/Characters/Protocol A.png");
	setTextureNSprite(NPC5, C3PO, 3.5, 1360, 440);

	NPC6.loadFromFile("Textures/Characters/Astro A.png");
	setTextureNSprite(NPC6, R4D4, 2.5, 1355, 350);

	NPC7.loadFromFile("Textures/Characters/Todo.png");
	setTextureNSprite(NPC7, Todo, 1, 343, 605);

	NPC8.loadFromFile("Textures/Characters/Lisa.png");
	setTextureNSprite(NPC8, Lisa, 1.5, 1290, 300);

	NPC9.loadFromFile("Textures/Characters/Solilas.png");
	setTextureNSprite(NPC9, Solilas, 1.5, 450, 50);

}

void SpaceShip::Update(RenderWindow& window, View& camera, float dt, int& collisionID) {
	speed = 500 * dt;
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (Keyboard::isKeyPressed(Keyboard::Right) && YourPlayer.getPosition().x < Background_Sprite.getPosition().x + Background_Sprite.getGlobalBounds().width - (Background_Sprite.getGlobalBounds().width * 0.17f))
		{
			YourPlayer.move(speed, 0);
			camera.move(speed, 0);
			y = 2;
			ChangeSprite(YourPlayer, dt, x, y, spriteTimer, spriteDelay, 64, 64, 4);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && YourPlayer.getPosition().x > Background_Sprite.getPosition().x + (Background_Sprite.getGlobalBounds().width * 0.01f))
		{
			YourPlayer.move(-speed, 0);
			camera.move(-speed, 0);
			y = 1;
			ChangeSprite(YourPlayer, dt, x, y, spriteTimer, spriteDelay, 64, 64, 4);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && YourPlayer.getPosition().y > Background_Sprite.getPosition().y + (Background_Sprite.getGlobalBounds().height * 0.13f))
		{
			YourPlayer.move(0, -speed);
			camera.move(0, -speed);
			y = 3;
			ChangeSprite(YourPlayer, dt, x, y, spriteTimer, spriteDelay, 64, 64, 4);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && YourPlayer.getPosition().y < Background_Sprite.getPosition().y + Background_Sprite.getGlobalBounds().height - (Background_Sprite.getGlobalBounds().height * 0.2f))
		{
			YourPlayer.move(0, speed);
			camera.move(0, speed);
			y = 0;
			ChangeSprite(YourPlayer, dt, x, y, spriteTimer, spriteDelay, 64, 64, 4);
		}

	}
	else {
		YourPlayer.setTextureRect(IntRect(0 * 64, y * 64, 64, 64));
	}

	ChangeSprite(Alien1, dt, n, l, alienSpriteTimer, alienSpriteDelay, 14, 19, 4);
	ChangeSprite(HellBoy, dt, n, l, alienSpriteTimer, alienSpriteDelay, 22, 35, 3);
	ChangeSprite(Elf, dt, g, l, alienSpriteTimer, alienSpriteDelay, 48, 81, 4);
	ChangeSprite(Todo, dt, h, l, alienSpriteTimer, alienSpriteDelay, 64, 64, 4);

	collisionID = 0;
	collison = false;

	Collision(GM_Sprite, YourPlayer, camera, speed, collisionID, 1, true);

	Collision(GM_Sprite5, YourPlayer, camera, speed, collisionID, 2, true);

	Collision(GM_Sprite4, YourPlayer, camera, speed, collisionID, 3, true);

	Collision(GM_Row2, YourPlayer, camera, speed);

	Collision(GM_Row1, YourPlayer, camera, speed);

	Collision(GM_Sprite2, YourPlayer, camera, speed, collisionID, 10, true);

	//Collision(GM_Row3, YourPlayer, camera, speed);

	Collision(BS1, YourPlayer, camera, speed, collisionID, 4, true);

	Collision(wall1, YourPlayer, camera, speed);

	Collision(wall3, YourPlayer, camera, speed);

	Collision(wall5, YourPlayer, camera, speed);

	Collision(VM, YourPlayer, camera, speed);

	Collision(Alien1, YourPlayer, camera, speed, collisionID, 5, true);

	Collision(HellBoy, YourPlayer, camera, speed);

	Collision(Nurse, YourPlayer, camera, speed);

	Collision(Elf, YourPlayer, camera, speed, collisionID, 9, true);

	Collision(Todo, YourPlayer, camera, speed, collisionID, 6, true);

	Collision(Solilas, YourPlayer, camera, speed, collisionID, 7, true);

	Collision(Lisa, YourPlayer, camera, speed, collisionID, 8, true);

	Render(window, camera, collisionID);
}

// Define the Render function of the space ship
void SpaceShip::Render(RenderWindow& window, View& camera, int collisionID) {

	window.draw(GM_Sprite);
	window.draw(wall5);
	window.draw(wall3);
	window.draw(wall1);
	window.draw(BS1);
	window.draw(BackS);
	window.draw(Background_Sprite);
	window.draw(GM_Sprite2);
	window.draw(GM_Sprite3);
	window.draw(GM_Sprite4);
	window.draw(GM_Sprite5);
	//window.draw(GM_Sprite5);
	window.draw(GM_Row1);
	window.draw(GM_Row2);
	//window.draw(GM_Row3);
	window.setView(camera);
	window.draw(VM);
	window.draw(Alien1);
	window.draw(HellBoy);
	window.draw(Nurse);
	window.draw(R4D4);
	window.draw(Elf);
	window.draw(C3PO);
	window.draw(Todo);
	window.draw(Lisa);
	window.draw(Solilas);
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
		case 5:
			window.draw(DBA);
			window.draw(Speech1);
			break;
		case 6:
			window.draw(DBB);
			window.draw(Speech2);
			break;
		case 7:
			window.draw(DBC);
			window.draw(Speech3);
			break;
		case 8:
			window.draw(DBD);
			window.draw(Speech4);
			break;
		case 9:
			window.draw(DBE);
			window.draw(Speech5);
			break;
		case 10:
			window.draw(DBF);
			window.draw(Speech6);
			break;
		}
	}
}


