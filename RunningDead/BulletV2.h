

#ifndef SFML_GAMEV3_BULLETV2_H
#define SFML_GAMEV3_BULLETV2_H


#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>



class BulletV2 {
private:
    sf::Sprite sprite; // Sprite for bullet
    sf::Vector2f velocity; // Vector for velocity
    bool active; // Bool to check if active


public:
    /*BulletV2(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction, float speed) {
        sprite.setTexture(texture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); // Set origin to center
        sprite.setPosition(position);
        sprite.setRotation(atan2(direction.y, direction.x) * 180 / M_PI); // Set rotation towards direction
        sprite.setScale(0.125f,0.125f);
        velocity = direction * speed;


    }*/
    // Constructor
    BulletV2(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
            : velocity(direction * speed) {
        sprite.setTexture(texture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); // Set origin to center
        sprite.setPosition(position);
        sprite.setRotation(atan2(direction.y, direction.x) * 180 / M_PI); // Set rotation towards direction
        sprite.setScale(0.125f,0.125f);
        velocity = direction * speed;
        active = true;
        sprite.setTextureRect(sf::IntRect(0, 21, 159, 150));


    }
    // Update function
    void update(float deltaTime) {
        // Scale the velocity vector by deltaTime
        sf::Vector2f deltaPosition = velocity * deltaTime;

        // Move the sprite by the scaled velocity
        sprite.move(deltaPosition);
    }

    // Function to draw the sprite to window
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    // Position getter
    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }
    // Sprite getter
    const sf::Sprite &getSprite() const {
        return sprite;
    }
    // Function to check collision
    void checkCollision(std::vector<Enemy>& enemies) {
        sf::FloatRect bulletBounds = sprite.getGlobalBounds(); // Get the global bounds of the bullet sprite

        for (auto& enemy : enemies) {
            sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds(); // Get the global bounds of the enemy sprite

            // Check if the bullet bounds intersect with the enemy bounds
            if (bulletBounds.intersects(enemyBounds)) {
                // If there's an intersection, handle the collision
                //std::cout << enemy.getHealth() << std::endl;
                std::cout << "hit detected" << std::endl;
                enemy.takeDamage(10);
                active = false; // Deactivate the bullet
                return; // Exit the loop early since the bullet can only collide with one enemy
            }
        }
    }

    // Active getter
    bool isActive() const {
        return active;
    }
    // Active setter
    void setActive(bool active) {
        BulletV2::active = active;
    }
};


#endif //SFML_GAMEV3_BULLETV2_H
