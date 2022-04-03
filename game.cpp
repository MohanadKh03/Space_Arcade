#include "game.h"
#include <math.h>
#include <time.h>

// Constructor
game::game(string title, int& score)
{
    //window.create(VideoMode(w, h), title);
    window.create(VideoMode::getFullscreenModes()[0], title, sf::Style::None);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    width = window.getSize().x;
    height = window.getSize().y;
    blocksWidth = (int)width / 80;
    blocksHeight = (int)height / 112;
    //user rectangle 
    paddle.setSize(Vector2f((int)width / 8, 20.0f));
    paddle.setFillColor(Color(80, 10, 10));
    paddle.setOutlineThickness(1.0f);
    paddle.setOutlineColor(Color(255, 255, 255));
    //ball
    ball.setRadius((float)width / 160);
    ball.setFillColor(/*Color(10, 80, 80)*/Color::White);
    ball.setOutlineThickness(1.0f);
    ball.setOutlineColor(Color(255, 255, 255));
    speedfactor = 5.0f;
    defaultspeed = 500.0f;
    angle = 0.0f;;

    // Drawing the UI
    font.loadFromFile("fonts/BodoniFLF-Bold.ttf");
    text.setFont(font);
    text.setString("Score : " + to_string(score));
    text.setFillColor(Color(50, 205, 50, 255));
    text.setCharacterSize(32);
    text.setPosition(0, 500);
    lives = 3;
    font.loadFromFile("fonts/BodoniFLF-Bold.ttf");
    textLife.setFont(font);
    textLife.setString("Life : " + to_string(lives));
    textLife.setFillColor(Color(50, 205, 50, 255));
    textLife.setCharacterSize(32);
    textLife.setPosition(0, 400);

    // special effects calls  /////////////////////////////////////////
    hitEffectTex.loadFromFile("effect.png");
    hitEffect.setTexture(hitEffectTex);
    hitEffect.setScale(Vector2f(window.getSize().x / 800, window.getSize().x / 800));
    hitEffect.setOrigin(18.5, 17);
    hitEffect.setRotation(90);

    reset();
    // Spawn Blocks
    for (int y = 0; y < blocksHeight; y++ /*block.getSize().y*/)
    {
        for (int x = 0; x < blocksWidth; x++ /*block.getSize().x*/)
        {
            int randomSize = 0;
            if (x == blocksWidth - 1) {
                randomSize = 1;
            }
            else {
                randomSize = (rand() % 2) + 1;
            }
            // Set each block
            blocks[y][x].setSize(Vector2f((width / blocksWidth) * randomSize, height / 18));
            blocks[y][x].setOutlineThickness(1.0f);
            blocks[y][x].setFillColor(Color::Red);
            blocks[y][x].setOutlineColor(Color::White);
            blocks[y][x].setPosition(Vector2f(x * (blocks[y][x].getSize().x / randomSize), y * (blocks[y][x].getSize().y)));
            if (randomSize == 2) {
                x++;
            }
            blockCount++;
        }
    }
}

void game::event(Event e)
{
    if (e.type == Event::Closed)
    {
        window.close();
    }
    //The Paddle Move With The Movement Of The Mouse 
    else if (e.type == Event::MouseMoved)
    {
        if (!paused) {
            paddle.setPosition(Vector2f(Mouse::getPosition(window).x - (paddle.getSize().x / 2), height - 40));
            //if The Paddle Smaller Than The Porder Of the Window From the Right Set It's Position From Zero
            if (paddle.getPosition().x < 0)
            {
                paddle.setPosition(Vector2f(0, paddle.getPosition().y));
            }
            else if (paddle.getPosition().x > width - paddle.getSize().x)
            {
                paddle.setPosition(Vector2f(width - paddle.getSize().x, paddle.getPosition().y));
            }
        }
    }
    else if (e.type == Event::MouseButtonPressed/* && lives <= 3 */ && lives > 0 && flag)
    {
        // If You Pressed the Mouse The Ball Will Get A Random Degree And Move In This Direction 
        ball.setPosition(Vector2f(paddle.getPosition().x + (paddle.getSize().x / 2) - ball.getRadius(), paddle.getPosition().y - paddle.getSize().y));
        angle = (-20 - (rand() % 140)) * (M_PI / 180.0);
        speed.x = cos(angle) * defaultspeed;
        speed.y = sin(angle) * defaultspeed;
        flag = false;
        cout << "Lives: " << lives << endl;
    }
    if (e.key.code == Keyboard::Escape) {
        if (!pressed) {
            paused = !paused;
            pressed = true;
        }
    }
    if (e.type == Event::KeyReleased) {
        if (e.key.code == Keyboard::Escape)
            pressed = false;
    }
}

void game::update(float dt, int& score)
{
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
        effectTimer -= 1 * dt;
    }

    if (speed.y == 0.0f)
    {
        //Set The Position Of The Ball To Middle Of The Paddle 
        ball.setPosition(Vector2f(paddle.getPosition().x + (paddle.getSize().x / 2) - ball.getRadius(), paddle.getPosition().y - paddle.getSize().y - ball.getRadius()));
    }
    else
    {
        ball.setPosition(Vector2f(ball.getPosition().x + (speed.x * dt), ball.getPosition().y + (speed.y * dt)));
        //Ball Boundry Collision
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
        else if (ball.getPosition().x + (ball.getRadius() * 2.0f) >= width)
        {
            // play the effect
            playEffect(Vector2f(window.getSize().x, ball.getPosition().y), -90);

            ball.setPosition(Vector2f(width - (ball.getRadius() * 2.0f), ball.getPosition().y));
            speed.x = -abs(speed.x);
        }
        //Lower Boundery
        else if (ball.getPosition().y + (ball.getRadius() * 2.0f) >= height)
        {
            reset();
            lives--;
            textLife.setString("Life: " + to_string(lives));

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
        }

        //Ball - Block Collision
        for (int y = 0; y < blocksHeight; y++)
        {
            for (int x = 0; x < blocksWidth; x++)
            {
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
        int killedBlockCount = 0;
        for (int y = 0; y < blocksHeight; y++) {
            for (int x = 0; x < blocksWidth; x++) {
                if (blocks[y][x].getScale() == Vector2f(0, 0)) {
                    killedBlockCount += 1;
                }
            }
        }
        if (killedBlockCount == blockCount || lives <= 0) {
            window.close();
        }
    }
}


void game::render()
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
    window.draw(textLife);
    window.draw(text);
    window.draw(hitEffect);
}

void game::reset()
{
    speed = Vector2f(0.0f, 0.0f);
    flag = true;
}

void game::run(int& score)
{
    Clock gameClock;
    float deltaTime = 0.0f;

    while (window.isOpen())
    {
        gameClock.restart();
        Event e;
        while (window.pollEvent(e))
        {
            event(e);
        }
        window.clear();
        update(deltaTime, score);
        render();
        window.display();
        deltaTime = gameClock.getElapsedTime().asSeconds();
    }
}

void game::playEffect(Vector2f position, float rotation) {
    effectTimer = effectDelay;
    spriteIndex = 0;
    hitEffect.setPosition(position);
    hitEffect.setRotation(rotation);
}