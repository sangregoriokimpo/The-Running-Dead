

#ifndef SFML_GAMEV3_ENEMY_H
#define SFML_GAMEV3_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
private:
    float attackRange; // Float for attack range
    int damage; // Integer for damage
    Player& player; // Reference to the player
    sf::Clock attackClock; // Clock to track attack cool down
    sf::Time attackCooldown; // Cool down between attacks

public:
    Enemy(sf::Texture& texture, float speed, int health, float attackRange, int damage, Player& player)
            : Entity(texture, speed, health), attackRange(attackRange), damage(damage), player(player), attackCooldown(sf::seconds(1.0f)) {
        // Set origin of the sprite to its center
        sprite.setTextureRect(sf::IntRect(57, 70, 193, 174));
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setScale(0.5f,0.5f);
    }


    void update(sf::RenderWindow& window, float deltaTime) {


        // Get the direction vector towards the player
        sf::Vector2f direction = player.getSprite().getPosition() - sprite.getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Ensure distance is not zero to avoid division by zero
        if (distance != 0) {
            // Normalize direction vector
            direction /= distance;

            // Move towards the player scaled by deltaTime
            sprite.move(direction * speed * deltaTime);

            // Rotate towards the player
            float angle = atan2(direction.y, direction.x) * 180 / 3.14159265;
            sprite.setRotation(angle);

            // Attack if within range and cooldown has elapsed
            if (distance <= attackRange && attackClock.getElapsedTime() >= attackCooldown) {
                player.takeDamage(damage);
                attackClock.restart(); // Restart the attack cool down timer
            }
        }
        if(distance == 0){
            if (distance <= attackRange && attackClock.getElapsedTime() >= attackCooldown) {
                player.takeDamage(damage);
                attackClock.restart(); // Restart the attack cool down timer
            }
        }
    }

    // Operator over loader for =
    Enemy& operator=(const Enemy& other) {
        if (this != &other) {
            this->player = other.player;
            this->attackClock = other.attackClock;
            this->damage = other.damage;
            this->attackCooldown = other.attackCooldown;
            this->attackRange = other.attackRange;
            this->speed = other.speed;
            this->health = other.health;
            this->healthBar = other.healthBar;
            this->healthBarSize = other.healthBarSize;
            this->sprite = other.sprite;
        }
        return *this;
    }

};





#endif //SFML_GAMEV3_ENEMY_H
