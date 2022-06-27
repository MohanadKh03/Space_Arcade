#include "Breaker.h"
#include <math.h>
#include <time.h>



// Constructor
// Set the initial values of the game's variables
game::game(RenderWindow* window, int& score)
{
    //rand seed
    srand(time(0));
    // No. of blocks on the screen
    blocksWidth = (int)window->getSize().x / 100;
    blocksHeight = (int)window->getSize().y / 130;
    // Paddle (player) 
    paddle.setSize(Vector2f((int)window->getSize().x / 8, 20.0f));
    paddle.setFillColor(Color::White);
    paddle.setPosition(Vector2f(window->getSize().x / 2 - (paddle.getSize().x / 2), window->getSize().y - 40));
    Paddle_texture.loadFromFile("Textures/Brick Breaker/56-Breakout-Tiles.png");
    paddle.setTexture(&Paddle_texture);
    // Balls
    ball.setRadius((float)window->getSize().x / 160);
    ball.setFillColor(Color::White);
    speedfactor = 50.0f;
    defaultspeed = 500.0f;
    Ball_texture.loadFromFile("Textures/Brick Breaker/58-Breakout-Tiles.png");
    ball.setTexture(&Ball_texture);
    angle = 0.0f;
    //// Ball Trail
    //ballTrail[0].setFillColor(Color::White);
    //ballTrail[0].setRadius(ball.getRadius());
    //ballTrail[0].setPosition(ball.getPosition());
    //for (int i = 1; i < 20; i++) {
    //    ballTrail[i].setPosition(ballTrail[i - 1].getPosition());
    //    ballTrail[i].setFillColor(ballTrail[i - 1].getFillColor() - Color(0, 0, 0, 12));
    //    ballTrail[i].setRadius(ballTrail[i - 1].getRadius() - 0.5f);
    //}

    // Draw the UI
    font.loadFromFile("Fonts/JosefinSans-Bold.ttf");
    text.setFont(font);
    score = 0;
    text.setString("Score : " + to_string(score));
    text.setFillColor(Color(50, 205, 50, 255));
    text.setCharacterSize(32);
    text.setPosition(10, 10);
    lives = 3;
    font.loadFromFile("Fonts/JosefinSans-Bold.ttf");
    textLife.setFont(font);
    textLife.setString("Lives : " + to_string(lives));
    textLife.setFillColor(Color(50, 205, 50, 255));
    textLife.setCharacterSize(32);
    textLife.setOrigin(textLife.getLocalBounds().width, textLife.getLocalBounds().height);
    textLife.setPosition(window->getSize().x - 10, textLife.getLocalBounds().height + 10);

    // special effects calls  /////////////////////////////////////////
    hitEffectTex.loadFromFile("Textures/Brick Breaker/effect.png");
    hitEffect.setTexture(hitEffectTex);
    hitEffect.setScale(Vector2f(window->getSize().x / 800, window->getSize().y / 800));
    hitEffect.setOrigin(18.5, 17);
    hitEffect.setRotation(90);

    bgBuffer.loadFromFile("Sounds/Brick Breaker/Breaker.wav");
    bgMusic.setBuffer(bgBuffer);
    bgMusic.setVolume(50.0f);
    bgMusic.play();
    bgMusic.setLoop(true);

    effectBuffer.loadFromFile("Sounds/Brick Breaker/Brick.wav");
    effectSound.setBuffer(effectBuffer);

    loseBuffer.loadFromFile("Sounds/Brick Breaker/Breaker-Lose.wav");
    loseSound.setBuffer(loseBuffer);
    //blocks Textures
    brick1.loadFromFile("Textures/Brick Breaker/Yellow.jpeg");
    brick2.loadFromFile("Textures/Brick Breaker/Red.jpeg");
    brick3.loadFromFile("Textures/Brick Breaker/Green.jpeg");
    brick4.loadFromFile("Textures/Brick Breaker/Purple.jpeg");
    brick5.loadFromFile("Textures/Brick Breaker/Blue.jpeg");
    brick6.loadFromFile("Textures/Brick Breaker/Lightblue.jpeg");
    brick7.loadFromFile("Textures/Brick Breaker/Lightgreen.jpeg");
    brick8.loadFromFile("Textures/Brick Breaker/Gray.jpeg");
    brick9.loadFromFile("Textures/Brick Breaker/Brown.jpeg");
    brick10.loadFromFile("Textures/Brick Breaker/Orange.jpeg");

    Background.loadFromFile("Textures/Brick Breaker/BlackBG.jpg");
    Backsprite.setTexture(Background);

    reset();
    score = 0;

    // Spawn Blocks
    for (int y = 0; y < blocksHeight; y++)
    {
        int lastRandColor = 0;
        for (int x = 0; x < blocksWidth; x++)
        {
            // Create random variable for each block's size
            int randomSize = 0;
            if (x == blocksWidth - 1) {
                randomSize = 1;
            }
            else {
                randomSize = (rand() % 2) + 1;
            }
            // Set each block
            blocks[y][x].setSize(Vector2f((window->getSize().x / blocksWidth) * randomSize - 2, window->getSize().y / 16 - 2));
            blocks[y][x].setOutlineThickness(1.0f);
            int randomColor = rand() % 10;
            while (randomColor == lastRandColor)
            {
                randomColor = rand() % 10;
            }
            switch (randomColor)
            {
            case 0:
                blocks[y][x].setTexture(&brick1);
                break;
            case 1:
                blocks[y][x].setTexture(&brick2);
                break;
            case 2:
                blocks[y][x].setTexture(&brick3);
                break;
            case 3:
                blocks[y][x].setTexture(&brick4);
                break;
            case 4:
                blocks[y][x].setTexture(&brick5);
                break;
            case 5:
                blocks[y][x].setTexture(&brick6);
                break;
            case 6:
                blocks[y][x].setTexture(&brick7);
                break;
            case 7:
                blocks[y][x].setTexture(&brick8);
                break;
            case 8:
                blocks[y][x].setTexture(&brick9);
                break;
            case 9 :
                blocks[y][x].setTexture(&brick10);
                break;
            }
            lastRandColor = randomColor;
            blocks[y][x].setOutlineColor(Color::Black);
            blocks[y][x].setPosition(Vector2f(x * ((blocks[y][x].getSize().x + 2) / randomSize), (y + 1) * (blocks[y][x].getSize().y + 2)));
            if (randomSize == 2) {
                x++;
            }
            blockCount++;
        }
    }
}

// Check for inputs
void game::event(RenderWindow& window, Event& e)
{
    // Check for pause input When Pressed Once
    if (e.key.code == Keyboard::P) {
        if (!pressed) {
            paused = !paused;
            pressed = true;
        }
    }
    if (e.type == Event::KeyReleased) {
        if (e.key.code == Keyboard::P)
            pressed = false;
    }

    //The Paddle Move With The Movement Of The Mouse 
    if (e.type == Event::MouseMoved)
    {
        if (!paused) {
            paddle.setPosition(Vector2f(Mouse::getPosition(window).x - (paddle.getSize().x / 2), window.getSize().y - 40));
            // Set paddle movement restrictions
            if (paddle.getPosition().x < 0)
            {
                paddle.setPosition(Vector2f(0, paddle.getPosition().y));
            }
            else if (paddle.getPosition().x > window.getSize().x - paddle.getSize().x)
            {
                paddle.setPosition(Vector2f(window.getSize().x - paddle.getSize().x, paddle.getPosition().y));
            }
            if (moveCheck % 2 == 0) {
                lastPosition = currentPosition;
            }
            if (moveCheck >= 500) {
                moveCheck = 0;
            }
            moveCheck++;

            if (currentPosition < lastPosition)
                direction = -1;
            else if (currentPosition > lastPosition)
                direction = 1;
            else
                direction = 0;
            currentPosition = paddle.getPosition().x;
        }
    }
    else if (e.type == Event::MouseButtonPressed && lives > 0 && flag)
    {
        // If You Pressed the Mouse The Ball Will Get A Random Degree And Move In This Direction 
        ball.setPosition(Vector2f(paddle.getPosition().x + (paddle.getSize().x / 2) - ball.getRadius(), paddle.getPosition().y - paddle.getSize().y));
        angle = (-20 - (rand() % 140)) * (M_PI / 180.0);
        speed.x = cos(angle) * defaultspeed;
        speed.y = sin(angle) * defaultspeed;
        flag = false;
    }
}

// Update each frame of the game
void game::update(RenderWindow* window, int& score, int& gameNUMBER)
{
    // Don't update when paused
    if (paused) {
        return;
    }

    // extras /////////////////////////////////////////
    hitEffect.setTextureRect(IntRect(spriteIndex * 37, 0, 37, 17));
    if (effectTimer <= 0 && spriteIndex < 6) {
        spriteIndex++;
        effectTimer = effectDelay;
    }
    else {
        effectTimer -= 1 * deltaTime;
    }

    //Set The Position Of The Ball To Middle Of The Paddle 
    if (speed.y == 0.0f)
        ball.setPosition(Vector2f(paddle.getPosition().x + (paddle.getSize().x / 2) - ball.getRadius(), paddle.getPosition().y - paddle.getSize().y - ball.getRadius()));
    else
    {
        // Ball position update
        ball.setPosition(Vector2f(ball.getPosition().x + (speed.x * deltaTime), ball.getPosition().y + (speed.y * deltaTime)));

        //// Ball trail update
        //ballTrail[0].setPosition(ball.getPosition());
        //for (int i = (sizeof(ballTrail) / sizeof(ballTrail[0]) - 1); i > 0; i--) {
        //    ballTrail[i].setPosition(ballTrail[i - 1].getPosition());
        //}


        //.......Ball Boundry Collision.......
        //Left Boundry
        if (ball.getPosition().x <= 0.0f)
        {
            // play the effect
            playEffect(Vector2f(0, ball.getPosition().y), 90);
            effectSound.play();

            ball.setPosition(Vector2f(0.0f, ball.getPosition().y));
            speed.x = abs(speed.x);
        }
        //Upper Boundry
        else if (ball.getPosition().y <= 0.0f)
        {
            // play the effect
            playEffect(Vector2f(ball.getPosition().x, 0), 180);
            effectSound.play();

            ball.setPosition(Vector2f(ball.getPosition().x, 0.0f));
            speed.y = abs(speed.y);
        }
        //Right Boundry
        else if (ball.getPosition().x + (ball.getRadius() * 2.0f) >= window->getSize().x)
        {
            // play the effect
            playEffect(Vector2f(window->getSize().x, ball.getPosition().y), -90);
            effectSound.play();

            ball.setPosition(Vector2f(window->getSize().x - (ball.getRadius() * 2.0f), ball.getPosition().y));
            speed.x = -abs(speed.x);
        }
        //Lower Boundery
        else if (ball.getPosition().y + (ball.getRadius() * 2.0f) >= window->getSize().y)
        {
            loseSound.play();
            reset();
            lives--;
            textLife.setString("Lives: " + to_string(lives));

        }
        //Ball Paddle Collisions 
        //If The Ball position Greater than The Paddle Thickness set Position To The Top Of The Paddle And The Change Its 
        //Speed Direction in Y axis 
        if (ball.getPosition().x + (ball.getRadius() * 2.0f) >= paddle.getPosition().x &&
            ball.getPosition().y + (ball.getRadius() * 2.0f) >= paddle.getPosition().y &&
            ball.getPosition().x < paddle.getPosition().x + paddle.getSize().x &&
            ball.getPosition().y < paddle.getPosition().y + paddle.getSize().y)
        {
            effectSound.play();
            float ratio = abs(speed.x) / abs(speed.y);
            //Increase Speed In Negative Direction
            if (speed.x < 0)
                speed.x -= speedfactor;
            else
                speed.x += speedfactor;
            if (speed.y < 0)
                speed.y -= speedfactor * ratio;
            else
                speed.y += speedfactor * ratio;
            ball.setPosition(Vector2f(ball.getPosition().x, paddle.getPosition().y - (ball.getRadius() * 2.0f)));
            speed.y = -abs(speed.y);
            //if The Paddle is Moving Right The Ball Will Move Right 
            if (direction == 1) {
                speed.x = cos(45 * (M_PI / 180.0)) * defaultspeed + speedfactor * ratio;
            }
            //if The Paddle Is Moving left The Ball Will Move Left  
            else if (direction == -1) {
                speed.x = cos(135 * (M_PI / 180.0)) * defaultspeed - speedfactor * ratio;
            }
        }

        //Ball - Block Collision
        for (int y = 0; y < blocksHeight; y++)
        {
            for (int x = 0; x < blocksWidth; x++)
            {
                // Check for collision and direction of it
                if (ball.getGlobalBounds().intersects(blocks[y][x].getGlobalBounds())) {
                    blocks[y][x].setScale(Vector2f(0, 0));
                    //Collision Of The Ball On The Left Of The Block
                    if (ball.getPosition().x + (ball.getRadius() * 2.0f) < blocks[y][x].getPosition().x) {
                        playEffect(Vector2f(ball.getPosition().x, ball.getPosition().y), -90);
                        speed.x = -speed.x;
                    }
                    else if (ball.getPosition().x + (ball.getRadius() * 2.0f) >= blocks[y][x].getPosition().x + blocks[y][x].getSize().x) {
                        playEffect(Vector2f(ball.getPosition().x, ball.getPosition().y), 90);
                        speed.x = -speed.x;
                    }
                    else if (ball.getPosition().y + (ball.getRadius() * 2.0f) >= blocks[y][x].getPosition().y + blocks[y][x].getSize().y - 40) {
                        playEffect(Vector2f(ball.getPosition().x, ball.getPosition().y), 180);
                        speed.y = -speed.y;
                    }
                    else if (ball.getPosition().y + (ball.getRadius() * 2.0f) < blocks[y][x].getPosition().y + 5) {
                        playEffect(Vector2f(ball.getPosition().x, ball.getPosition().y), 0);
                        speed.y = -speed.y;
                    }
                    effectSound.play();
                    score++;
                    text.setString("Score : " + to_string(score));
                }
            }
        }
        // Check for WIN or LOSE  conditions
        int killedBlockCount = 0;
        for (int y = 0; y < blocksHeight; y++) {
            for (int x = 0; x < blocksWidth; x++) {
                if (blocks[y][x].getScale() == Vector2f(0, 0)) {
                    killedBlockCount += 1;
                }
            }
        }
        if (killedBlockCount == blockCount || lives <= 0) {
            gameNUMBER = 0;
        }
    }
}

// Render the game 
void game::render(RenderWindow& window)
{
    window.draw(Backsprite);
    // Spawn Blocks
    for (int y = 0; y < blocksHeight; y++)
    {
        for (int x = 0; x < blocksWidth; x++)
        {
            // Set each block
            window.draw(blocks[y][x]);
        }
    }
    window.draw(paddle);
    window.draw(ball);
 /*   if (speed.y != 0)
        for (int i = 0; i < 20; i++)
            window.draw(ballTrail[i]);
    else
        for (int i = 0; i < 20; i++)
            ballTrail[i].setPosition(ball.getPosition());*/
    window.draw(textLife);
    window.draw(text);
    window.draw(hitEffect);
}

// Reset the position of the ball
void game::reset()
{
    speed = Vector2f(0.0f, 0.0f);
    flag = true;
}

// Run the whole game
void game::run(RenderWindow& window, Event& e, int& score, int& gameNUMBER)
{
    render(window);
    update(&window, score, gameNUMBER);
}

// Play the splash effect
void game::playEffect(Vector2f position, float rotation) {
    effectTimer = effectDelay;
    spriteIndex = 0;
    hitEffect.setPosition(position);
    hitEffect.setRotation(rotation);
}