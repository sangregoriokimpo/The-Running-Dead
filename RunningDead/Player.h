

#ifndef SFML_GAMEV3_PLAYER_H
#define SFML_GAMEV3_PLAYER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>


class Player : public Entity{
private:
    float rotationSpeed;


public:
    //Constructor
    Player(sf::Texture& texture, float speed, int health, float rotationSpeed)
            : Entity(texture, speed, health), rotationSpeed(rotationSpeed) {}

    void update(sf::RenderWindow& window, float deltaTime){
        // Movement based on keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            sprite.move(0, -Entity::speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            sprite.move(0, Entity::speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            sprite.move(-Entity::speed * deltaTime, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            sprite.move(Entity::speed * deltaTime, 0);

        // Rotation towards mouse
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);
        float angle = atan2(worldMousePosition.y - sprite.getPosition().y,worldMousePosition.x - sprite.getPosition().x) * 180 / M_PI;


        sprite.setRotation(angle);


        // Draw line to mouse
        drawLineToMouse(window);

        if(health == 0){//Close window if player dies
            window.close();
        }
    }


    void drawLineToMouse(sf::RenderWindow& window) {
        // Get the world mouse position (window coordinates to world coordinates)
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // Calculate the direction vector from the player to the mouse
        sf::Vector2f direction = worldMousePosition - sprite.getPosition();

        // Calculate the length of the direction vector
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalize the direction vector
        direction /= length;

        // Create a vertex array for the line
        sf::VertexArray line(sf::LinesStrip);

        // Add the player's position as the first vertex
        line.append(sf::Vertex(sprite.getPosition(), sf::Color::Red));

        // Define the gradient colors (start and end colors)
        sf::Color startColor(255, 0, 0); // Red
        sf::Color endColor(255, 255, 255); // White

        // Calculate the color step for each vertex
        float colorStep = 1.0f / length;
        sf::Color currentColor = startColor;

        // Interpolate colors along the line and add vertices to the vertex array
        for (float i = 0; i < length; ++i) {
            sf::Color interpolatedColor = sf::Color(
                    static_cast<sf::Uint8>((1.0f - i * colorStep) * startColor.r + i * colorStep * endColor.r),
                    static_cast<sf::Uint8>((1.0f - i * colorStep) * startColor.g + i * colorStep * endColor.g),
                    static_cast<sf::Uint8>((1.0f - i * colorStep) * startColor.b + i * colorStep * endColor.b)
            );
            line.append(sf::Vertex(sprite.getPosition() + i * direction, interpolatedColor));
        }

        // Add the mouse position as the last vertex
        line.append(sf::Vertex(worldMousePosition, sf::Color::White));

        // Draw the line
        window.draw(line);
    }



};


#endif //SFML_GAMEV3_PLAYER_H
