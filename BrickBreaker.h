#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"

using namespace sf;

void gameGameLoop(int& screenWidth, int& screenHeight, int& score) {
    // Creating a render window
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Brick Breaker Game", Style::Close);
    window.setFramerateLimit(60);

    // Creating the time and delta time (watch a simple tutorial on utube
    float dt = 0;
    Clock dtClock;

    // Creating the player and setting it's initial values
    RectangleShape player;
    player.setSize(Vector2f(100, 10));
    player.setFillColor(Color::Red);
    player.setOrigin(50, 5);
    player.setPosition(screenWidth / 2, screenHeight - 50);
    // Creating a Vector2f variable to hold the offset of the ball from the center (origin) of the player
    Vector2f offset = Vector2f(0, -player.getSize().y);

    // Create and instance of a ball
    Ball ball(player, window, offset, 500);

    // Start the game loop
    while (window.isOpen()) {
        // reset the time counter so it counts from the start of the frame
        dt = dtClock.restart().asSeconds();

        // Create and event
        Event event;
        // Check for events
        while (window.pollEvent(event)) {
            // If the event is the user closing the game, exit the game
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // If the player
        if (ball.lives > 0) {
            if (Keyboard::isKeyPressed(Keyboard::Right) && ball.lives > 0) {
                player.move(Vector2f(500, 0) * dt);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left) && ball.lives > 0) {
                player.move(Vector2f(-500, 0) * dt);
            }
            else {
                player.move(Vector2f(0, 0));
            }
        }
        else {
            player.move(Vector2f(0, 0));
        }

        // Update the ball's status (position, collision, and other stuff)
        ball.Update(window, player, dt, score);

        // Clearing then drawing the background with the player, ball and the hit effect of the ball
        window.clear(Color::Black);
        window.draw(player);
        window.draw(ball.ball);
        window.draw(ball.hitEffect);
        // Display the window
        window.display();
    }
}