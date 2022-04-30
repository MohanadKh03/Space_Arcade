#include "Breaker.h"
#include <math.h>
#include <time.h>

// Constructor
// Set the initial values of the game's variables
game::game(RenderWindow* window, int& score)
{
    // No. of blocks on the screen
    blocksWidth = (int)window->getSize().x / 80;
    blocksHeight = (int)window->getSize().y / 150;
    // Paddle (player) 
    paddle.setSize(Vector2f((int)window->getSize().x / 8, 20.0f));
    paddle.setFillColor(Color::White);
    paddle.setPosition(Vector2f(window->getSize().x/2 - (paddle.getSize().x / 2), window->getSize().y - 40));
    // Balls
    ball.setRadius((float)window->getSize().x / 160);
    ball.setFillColor(Color::White);
    speedfactor = 5.0f;
    defaultspeed = 500.0f;
    angle = 0.0f;
    // Ball Trail
    ballTrail[0].setFillColor(Color::White);
    ballTrail[0].setRadius(ball.getRadius());
    ballTrail[0].setPosition(ball.getPosition());
    for (int i = 1; i < 20; i++) {
        ballTrail[i].setPosition(ballTrail[i - 1].getPosition());
        ballTrail[i].setFillColor(ballTrail[i-1].getFillColor() - Color(0,0,0,12));
        ballTrail[i].setRadius(ballTrail[i - 1].getRadius() - 0.5f);
    }

    // Draw the UI
    font.loadFromFile("fonts/JosefinSans-Bold.ttf");
    text.setFont(font);
    text.setString("Score : " + to_string(score));
    text.setFillColor(Color(50, 205, 50, 255));
    text.setCharacterSize(32);
    text.setPosition(10,10);
    lives = 3;
    font.loadFromFile("fonts/JosefinSans-Bold.ttf");
    textLife.setFont(font);
    textLife.setString("Lives : " + to_string(lives));
    textLife.setFillColor(Color(50, 205, 50, 255));
    textLife.setCharacterSize(32);
    textLife.setOrigin(textLife.getLocalBounds().width, textLife.getLocalBounds().height);
    textLife.setPosition(window->getSize().x - 10, textLife.getLocalBounds().height + 10);

    // special effects calls  /////////////////////////////////////////
    hitEffectTex.loadFromFile("effect.png");
    hitEffect.setTexture(hitEffectTex);
    hitEffect.setScale(Vector2f(window->getSize().x / 800, window->getSize().y / 800));
    hitEffect.setOrigin(18.5, 17);
    hitEffect.setRotation(90);

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
            blocks[y][x].setSize(Vector2f((window->getSize().x / blocksWidth) * randomSize - 2, window->getSize().y / 18 - 2));
            blocks[y][x].setOutlineThickness(1.0f);
            int randomColor = rand() % 5;
            while (randomColor == lastRandColor)
            {
                randomColor = rand() % 5;
            }
            switch (randomColor)
            {
            case 0:
                blocks[y][x].setFillColor(Color::Blue);
                break;
            case 1:
                blocks[y][x].setFillColor(Color::Red);
                break;
            case 2:
                blocks[y][x].setFillColor(Color::Green);
                break;
            case 3:
                blocks[y][x].setFillColor(Color::Magenta);
                break;
            case 4:
                blocks[y][x].setFillColor(Color::Yellow);
                break;
            }
            lastRandColor = randomColor;
            blocks[y][x].setOutlineColor(Color::White);
            blocks[y][x].setPosition(Vector2f(x * ((blocks[y][x].getSize().x + 2) / randomSize), (y+1) * (blocks[y][x].getSize().y+2)));
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
    // Check for pause input
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
            if (moveCheck % 5 == 0) {
                lastPosition = currentPosition;
            }
            if (moveCheck >= 500) {
                moveCheck = 0;
            }
            moveCheck++;

            if (currentPosition < lastPosition) {
                direction = -1;
            }
            else if (currentPosition > lastPosition) {
                direction = 1;
            }
            else
            {
                direction = 0;
            }
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
void game::update(RenderWindow* window, int& score,int& gameNUMBER)
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
        
        // Ball trail update
        ballTrail[0].setPosition(ball.getPosition());
        for (int i = 19; i > 0; i--) {
            ballTrail[i].setPosition(ballTrail[i - 1].getPosition());
        }
        

        //.......Ball Boundry Collision.......
        //Left Boundry
        if (ball.getPosition().x <= 0.0f)
        {
            // play the effect
            playEffect(Vector2f(0, ball.getPosition().y), 90);

            ball.setPosition(Vector2f(0.0f, ball.getPosition().y));
            speed.x = abs(speed.x);
        }
        //Upper Boundry
        else if (ball.getPosition().y <= 0.0f)
        {
            // play the effect
            playEffect(Vector2f(ball.getPosition().x, 0), 180);

            ball.setPosition(Vector2f(ball.getPosition().x, 0.0f));
            speed.y = abs(speed.y);
        }
        //Right Boundry
        else if (ball.getPosition().x + (ball.getRadius() * 2.0f) >= window->getSize().x)
        {
            // play the effect
            playEffect(Vector2f(window->getSize().x, ball.getPosition().y), -90);

            ball.setPosition(Vector2f(window->getSize().x - (ball.getRadius() * 2.0f), ball.getPosition().y));
            speed.x = -abs(speed.x);
        }
        //Lower Boundery
        else if (ball.getPosition().y + (ball.getRadius() * 2.0f) >= window->getSize().y)
        {
            reset();
            lives--;
            textLife.setString("Lives: " + to_string(lives));

        }
        //Ball Paddle Collisions 
        //If The Ball position Greater than The Paddle Thickness set Position To The Top Of The Paddle And The Change It's 
        //Speed Direction in Y axis 
        if (ball.getPosition().x + (ball.getRadius() * 2.0f) >= paddle.getPosition().x &&
            ball.getPosition().y + (ball.getRadius() * 2.0f) >= paddle.getPosition().y &&
            ball.getPosition().x < paddle.getPosition().x + paddle.getSize().x &&
            ball.getPosition().y < paddle.getPosition().y + paddle.getSize().y)
        {
            float ratio = abs(speed.x) / abs(speed.y);
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
            if (direction == 1) {
                speed.x = cos(45 * (M_PI / 180.0)) * defaultspeed;
            }
            else if (direction == -1) {
                speed.x = cos(135 * (M_PI / 180.0)) * defaultspeed;
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
    if (speed.y != 0)
        for (int i = 0; i < 20; i++)
            window.draw(ballTrail[i]);
    else 
        for (int i = 0; i < 20; i++)
            ballTrail[i].setPosition(ball.getPosition());
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
void game::run(RenderWindow& window, Event& e, int& score,int& gameNUMBER)
{
    render(window);
    update(&window, score,gameNUMBER);
}

// Play the splash effect
void game::playEffect(Vector2f position, float rotation) {
    effectTimer = effectDelay;
    spriteIndex = 0;
    hitEffect.setPosition(position);
    hitEffect.setRotation(rotation);
}