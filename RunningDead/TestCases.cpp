//
// Created by Gregory Jabido on 4/24/24.
//

#include "TestCases.h"

void TestCases::testEnemyDamage() {
    // Load enemy texture
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../export/skeleton-attack_0.png")) {
        // Handle error loading texture
        cout << "Failure to read file" << endl;
    }

    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../Top_Down_Survivor/rifle/idle/survivor-idle_rifle_0.png")) {
        // Handle error loading texture
        cout << "Failure to read file" << endl;
    }

    Player testPlayer(playerTexture,200,100,5);

    Enemy testEnemy(enemyTexture,50.0f,100.0f,10.0f,10.0f,testPlayer);
    cout << "Enemy Health: "<< testEnemy.getHealth() << endl;
    cout << "Taking 10 damage" << endl;
    testEnemy.takeDamage(10);
    cout << "Enemy Health: "<< testEnemy.getHealth() << endl;
    cout << "Test Enemy Damage success" << endl;
}

void TestCases::testPlayerDamage() {
    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../Top_Down_Survivor/rifle/idle/survivor-idle_rifle_0.png")) {
        // Handle error loading texture
        cout << "Failure to read file" << endl;
    }

    Player testPlayer(playerTexture,200.0f,100.0f,5.0f);
    cout << "Player Health: " << testPlayer.getHealth() << endl;
    cout << "Taking 10 damage" << endl;
    testPlayer.takeDamage(10);
    cout << "Player Health: "<< testPlayer.getHealth() << endl;
    cout << "Test Player Damage success" << endl;
}

void TestCases::testPlayerHealthBar() {
    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../Top_Down_Survivor/rifle/idle/survivor-idle_rifle_0.png")) {
        // Handle error loading texture
        cout << "Failure to read file" << endl;
    }

    Player testPlayer(playerTexture,200.0f,100.0f,5.0f);
    cout << "Player Health: " << testPlayer.getHealth() << endl;
    cout << "Taking 10 damage" << endl;
    testPlayer.takeDamage(10);
    cout << "x: " << testPlayer.getHealthBarSize().x << " y:" << testPlayer.getHealthBarSize().y << endl;
    cout << "Player Health: "<< testPlayer.getHealth() << endl;
    cout << "Test Player health bar success" << endl;
}

void TestCases::testBulletConstructor() {
    sf::Texture bulletTexture;
    if(!bulletTexture.loadFromFile("../bullets/frame_0.png")){
        cout << "Failure to read file" << endl;
    }
    sf::Vector2f initialPosition(100.0f, 100.0f);
    sf::Vector2f direction(1.0f, 0.0f); // Move horizontally to the right
    float speed = 200.0f;
    BulletV2 testBullet(bulletTexture, initialPosition, direction, speed);
    // Define a delta time for the update
    float deltaTime = 0.5f; // Half a second

    // Update the bullet with the defined delta time
    testBullet.update(deltaTime);

    cout << "x: " << testBullet.getPosition().x << " y:" << testBullet.getPosition().y << endl;
    cout << "Bullet successfully constructed" << endl;

}

void TestCases::testSpawnHandler() {
    // Load enemy texture
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../export/skeleton-attack_0.png")) {
        // Handle error loading texture
        cout << "Failure to read file" << endl;
    }
    sf::Texture bulletTexture;
    if(!bulletTexture.loadFromFile("../bullets/frame_0.png")){
        cout << "Failure to read file" << endl;
    }
    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../Top_Down_Survivor/rifle/idle/survivor-idle_rifle_0.png")) {
        // Handle error loading texture
        cout << "Failure to read file" << endl;
    }
    Player testPlayer(playerTexture,200.0f,100.0f,5.0f);

    // Define initial position, direction, and speed of the bullet
    sf::Vector2f initialPosition(100.0f, 100.0f);
    sf::Vector2f direction(1.0f, 0.0f); // Move horizontally to the right
    float speed = 200.0f;
    // Create a bullet object
    BulletV2 bullet(bulletTexture, initialPosition, direction, speed);
    // Define a vector of enemies for collision checking
    std::vector<Enemy> enemies;
    // Add an enemy at the same position as the bullet
    Enemy testEnemy(enemyTexture,50.0f,100.0f,10.0f,10.0f,testPlayer);
    testEnemy.getSprite().setPosition(5.0f,0);
    SpawnHandler spawnHandler(enemies, enemyTexture, testPlayer, sf::seconds(1.0f));
    // Add the enemy to the vector of enemies
    testEnemy.takeDamage(100.0f);
    enemies.emplace_back(testEnemy);
    spawnHandler.removeDeadEnemies();
    cout << "Enemies alive: " << enemies.size() << endl;
    cout << "Spawn handler test dead enemy removal success" << endl;

}

TestCases::TestCases() {
//Constructor
}

void TestCases::runAllTests() {
    // Run test for enemy damage
    testEnemyDamage();
    // Run test for player damage
    testPlayerDamage();
    // Run test for player health bar
    testPlayerHealthBar();
    // Run test for bullet constructor
    testBulletConstructor();
    // Run test for spawn handler
    testSpawnHandler();
}
