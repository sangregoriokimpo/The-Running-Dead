

#ifndef SFML_GAMEV3_ENTITY_H
#define SFML_GAMEV3_ENTITY_H

#include <SFML/Graphics.hpp>



class Entity {
protected:
    sf::Sprite sprite; // sprite
    float speed; // float for speed
    int health; // integer for health
    sf::RectangleShape healthBar; // Rectangle shape for health bar
    sf::Vector2f healthBarSize; // Vector for health bar size

public:
    Entity(sf::Texture& texture, float speed, int health)
            : speed(speed), health(health) {
        sprite.setTexture(texture);
        // Set origin to center for rotation
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

        // Initialize health bar
        healthBarSize = sf::Vector2f(50, 5); // Set size of the health bar
        healthBar.setSize(healthBarSize); // Set initial size
        healthBar.setFillColor(sf::Color::Green); // Set color
        healthBar.setPosition(sprite.getPosition().x - healthBarSize.x / 2, sprite.getPosition().y + sprite.getLocalBounds().height / 2 + 5); // Position below the sprite
        healthBar.setOutlineThickness(1); // Optional: add outline
        healthBar.setOutlineColor(sf::Color::Black); // Optional: outline color
    }

    virtual void update(sf::RenderWindow& window, float deltaTime) = 0;

    //Sprite getter
    sf::Sprite& getSprite() {
        return sprite;
    }
    //Health getter
    int getHealth() const {
        return health;
    }
    //Take damage function
    void takeDamage(int damage) {
        health -= damage;//decrement health
        // Ensure health doesn't go below 0
        health = std::max(health, 0);
        updateHealthBar(); // Update health bar
    }

    virtual ~Entity() {
        //Destructor
    }

    // Update health bar size based on health
    void updateHealthBar() {
        float ratio = static_cast<float>(health) / 100; // Calculate health ratio
        healthBar.setSize(sf::Vector2f(healthBarSize.x * ratio, healthBarSize.y)); // Adjust width of health bar
    }

    // Function to update health bar position based on sprite position
    void updateHealthBarPosition() {
        // Update health bar position relative to the sprite
        healthBar.setPosition(sprite.getPosition().x - healthBarSize.x / 2, sprite.getPosition().y - sprite.getLocalBounds().height / 2 - 4);
    }



    // Draw the entity and its health bar
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        updateHealthBarPosition();
        window.draw(healthBar);
    }

    // Size of the health bar
    const sf::Vector2f &getHealthBarSize() const {
        return healthBarSize;
    }


};

#endif //SFML_GAMEV3_ENTITY_H
