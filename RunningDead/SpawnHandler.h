

#ifndef SFML_GAMEV3_SPAWNHANDLER_H
#define SFML_GAMEV3_SPAWNHANDLER_H

#include "Enemy.h"
#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


class SpawnHandler {
private:
    std::vector<Enemy>& enemies; // Reference to the vector containing enemy objects
    sf::Texture enemyTexture; // Texture for creating new enemies
    Player& player; // Reference to the player
    sf::Time spawnInterval; // Interval between enemy spawns
    sf::Clock spawnClock; // Clock to track spawn time
    int kills = 0;

public:
    SpawnHandler(std::vector<Enemy>& enemies, sf::Texture enemyTexture,Player& player, const sf::Time& spawnInterval)
            : enemies(enemies), enemyTexture(enemyTexture), player(player), spawnInterval(spawnInterval) {}

    void update(sf::RenderWindow& window,float deltaTime) {
        // Check if it's time to spawn a new enemy
        if (spawnClock.getElapsedTime() >= spawnInterval) {
            // Spawn a new enemy
            spawnEnemy(window);
            // Restart the spawn clock
            spawnClock.restart();
        }
        for(auto& enemy: enemies){
            enemy.update(window,deltaTime);
        }
    }

    void spawnEnemy(sf::RenderWindow& window) {
        // Get the size of the window
        sf::Vector2u windowSize = window.getSize();

        // Get the player's current position
        sf::Vector2f playerPosition = player.getSprite().getPosition();

        // Determine the direction relative to the player's position
        float xOffset, yOffset;
        if (playerPosition.x < windowSize.x / 2) {
            // Player is on the left side of the window
            xOffset = -static_cast<float>(rand() % 200 + 100); // Spawn to the left
        } else {
            // Player is on the right side of the window
            xOffset = static_cast<float>(windowSize.x) + static_cast<float>(rand() % 200 + 100); // Spawn to the right
        }

        if (playerPosition.y < windowSize.y / 2) {
            // Player is on the top side of the window
            yOffset = -static_cast<float>(rand() % 200 + 100); // Spawn above
        } else {
            // Player is on the bottom side of the window
            yOffset = static_cast<float>(windowSize.y) + static_cast<float>(rand() % 200 + 100); // Spawn below
        }

        // Create and add a new enemy at the calculated coordinates
        enemies.emplace_back(enemyTexture, 250.0f, 100, 100.0f, 10, player);
        enemies.back().getSprite().setPosition(playerPosition.x + xOffset, playerPosition.y + yOffset);
    }



    // Remove a dead enemy from the vector
    void removeDeadEnemies() {
        // Iterate through the vector of enemies
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            // Check if the enemy is dead
            if (it->getHealth() <= 0) {
                // Erase the enemy from the vector
                kills++;
                it = enemies.erase(it);
                std::cout << "Zombies Slayed: " << kills << std::endl;
            } else {
                ++it;
            }
        }
    }

    // Draw all enemies
    void drawEnemies(sf::RenderWindow& window) {
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
    }


};




#endif //SFML_GAMEV3_SPAWNHANDLER_H
