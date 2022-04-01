#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <time.h>
#include <math.h>

using namespace sf;
using namespace std;

// create a ball class
class Ball
{
    // set the public variables and methods of the ball class
public:
    // define the constructor
    Ball(RectangleShape refPlayer, RenderWindow& window, Vector2f refOffset, float speed);
    // define the destructor
    ~Ball();

    // make the ball with a circle shape till we get a sprite
    CircleShape ball;
    // define the initial radius of the ball
    float radius = 0;
    // define a variable to hold the offset of the ball from the center of the player
    Vector2f offset;
    // define a variable to hold the direction of the ball's movement
    Vector2f direction;
    // define a variable to hold the speed of the ball
    float speed;
    // define a variable to hold the lives of the player
    int lives = 5;

    // special effects variables /////////////////////////////////////////
    Sprite hitEffect;

    // define an update function to get called every single frame of the game
    void Update(RenderWindow& window, RectangleShape opPlayer, float dt, int& score /*, RectangleShape tile*/) {
        // if the player pressed the space button, start the game
        if (Keyboard::isKeyPressed(Keyboard::Space) && lives > 0) {
            // define a new seed for random numbers
            srand(time(0));
            // get a random angle to launch the ball in
            float angle = ((rand() % 90) + 45) * (float)(M_PI / 180);
            // set the initial direction of the ball's movement
            direction = Vector2f(cos(angle), -sin(angle));
            // start the game by setting the launched bool to true
            launched = true;
        }
        // check if the game started with the launched bool
        if (launched) {
            // move the player with (direction)
            ball.move(direction * speed * dt);
            // check for collisions
            bordersCollisions(window, opPlayer, score /*, tile*/);
        }
        else {
            if (lives > 0) {
                // set the position of the ball to the player because the game is lost or hasn't started yet
                ball.setPosition(opPlayer.getPosition() + offset);
            }
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
    }
    // set the private variables and methods of the ball class
private:
    // set a bool variable to hold the ball's condition (standing or moving)
    bool launched = false;

    // special effect variables /////////////////////////////////////////
    Texture hitEffectTex;
    int spriteIndex = 0;
    float effectTimer = 0;
    float effectDelay = 0.05f;

    // check for collisions with everything
    void bordersCollisions(RenderWindow& window, RectangleShape player, int& score /*, RectangleShape tile*/) {
        // check if the ball hit the right wall
        if (ball.getPosition().x >= window.getSize().x) {
            // play the effect
            playEffect(Vector2f(window.getSize().x, ball.getPosition().y), -90, score);

            // change the position of the ball to a reasonable position
            ball.setPosition(ball.getPosition() + Vector2f(-5, 0));
            // change the X direction of the ball
            direction.x = -1;
        }
        // check if the ball hit the left wall
        else if (ball.getPosition().x <= 0) {
            // play the effect
            playEffect(Vector2f(0, ball.getPosition().y), 90, score);

            // change the position of the ball to a reasonable position
            ball.setPosition(ball.getPosition() + Vector2f(5, 0));
            // change the X direction of the ball
            direction.x = 1;
        }
        // check if the ball hit the ceiling
        else if (ball.getPosition().y <= 0) {
            // play the effect
            playEffect(Vector2f(ball.getPosition().x, 0), 180, score);

            // change the position of the ball to a reasonable position
            ball.setPosition(ball.getPosition() + Vector2f(0, 5));
            // change the Y direction of the ball
            direction.y *= -1;
        }
        // check if the ball fell to it's death
        else if (ball.getPosition().y >= window.getSize().y) {
            // stop the game, so set the launched bool to false
            launched = false;
            // decrease the lives of the player by 1
            lives -= 1;
            // print out the remaining lives for debugging
            //cout << "LIVES: " << lives << endl;
        }
        // check if the ball touched the player
        else if (ball.getGlobalBounds().intersects(player.getGlobalBounds())) {
            // change the position of the ball to a reasonable position
            ball.setPosition(ball.getPosition() + Vector2f(0, -3));
            // the player hit the ball, so change the Y direction of the ball
            direction.y *= -1;
        }
    }

    // extra effects functions  /////////////////////////////////////////
    void playEffect(Vector2f position, float rotation, int& score) {
        effectTimer = effectDelay;
        spriteIndex = 0;
        hitEffect.setPosition(position);
        hitEffect.setRotation(rotation);
        score++;
    }
};

// define the constructor of the ball class
Ball::Ball(RectangleShape refPlayer, RenderWindow& CWindow, Vector2f refOffset, float outSpeed) {
    speed = outSpeed;
    offset = refOffset;
    RenderWindow& window = CWindow;
    // Set the intital position of the ball
    ball.setPosition(refPlayer.getPosition() + offset);
    // Set the intital radius of the ball
    ball.setRadius(window.getSize().y / 90);
    // Set the origin of the ball
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    // Set the fill color of the ball
    ball.setFillColor(Color::White);


    // special effects calls  /////////////////////////////////////////
    hitEffectTex.loadFromFile("effect.png");
    hitEffect.setTexture(hitEffectTex);
    hitEffect.setScale(Vector2f(window.getSize().x / 900, window.getSize().x / 900));
    hitEffect.setOrigin(18.5, 17);
    hitEffect.setRotation(90);
    hitEffect.setPosition(-100, -100);
}

// define the destructor of the ball class
Ball::~Ball() {

}
