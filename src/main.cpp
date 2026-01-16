#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    // --- creating a video mode obj
    VideoMode vm({800, 600});

    // --- create and open a window for the game
    RenderWindow window(vm, "Pong");

    int score = 0;
    int lives = 3;

    // --- creating a bat
    Bat bat(800 / 2, 600 - 20);

    // --- creating a ball
    Ball ball(800 / 2, 0);

    // --- FONT ---
    Font font;
    if (!font.openFromFile("../fonts/DepartureMono-Regular.otf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return EXIT_FAILURE;
    }

    // --- HUD ---
    Text hud(font, "", 20);
    hud.setFillColor(Color::White);
    hud.setPosition({20.0f, 20.0f});

    // --- clock for timing
    Clock clock;

    // -- flag to disable multiple collisions
    bool ballWasHit = false;

    while (window.isOpen())
    {
        // --- INPUT ---
        while (auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        // --- QUIT ---
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            window.close();
        }

        // --- CONTROLS ---
        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
            bat.moveLeft();
        }
        else
        {
            bat.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        {
            bat.moveRight();
        }
        else
        {
            bat.stopRight();
        }

        // --- UPDATING GAME OBJECTS ---
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);
        
        // --- UPDATING HUD TEXT ---
        std::stringstream ss;
        ss << "Score:" << score << "    Lives:" << lives;
        hud.setString(ss.str());

        // --- getting window size
        Vector2u windowSize = window.getSize();
        
        // --- rectangels for collision detecting
        FloatRect ballRect = ball.getPosition();
        FloatRect batRect = bat.getPosition();

        // --- BALL HITTING BOTTOM ---
        if (ballRect.position.y + ballRect.size.y > static_cast<float>(windowSize.y))
        {
            lives--;

            ball.reset(800 / 2, 0);
            ballWasHit = false;

            if (lives < 1) {
                score = 0;
                lives = 3;
            }
        }

        // --- BALL HITTING TOP ---
        if (ballRect.position.y < 0)
        {
            ball.reboundBatOrTop();
            ballWasHit = false;
        }

        // --- BALL HITTING SIDES ---
        if (ballRect.position.x < 0 ||
            ballRect.position.x + ballRect.size.x > static_cast<float>(windowSize.x))
        {
            ball.reboundSides();
        }

        // --- BALL HITTING BAT ---
        if (ballRect.findIntersection(batRect).has_value())
        {
            if (ball.getYVelocity() > 0 && !ballWasHit)
            {
                ball.reboundBatOrTop();
                score++;
                ballWasHit = true;
            }
        }
        else
        {
            ballWasHit = false;
        }

        // --- DRAW EVERYTHING ---
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }

    return 0;
}