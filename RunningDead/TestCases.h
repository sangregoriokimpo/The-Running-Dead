//
// Created by Gregory Jabido on 4/24/24.
//

#ifndef RUNNINGDEAD_TESTCASES_H
#define RUNNINGDEAD_TESTCASES_H

#include "Enemy.h"
#include "Player.h"
#include "Entity.h"
#include "SpawnHandler.h"
#include "ShootingSystemV2.h"
#include "BulletV2.h"
#include <iostream>

using std::endl;
using std::cout;

class TestCases {

public:
    // Test case to test enemy damage
    void testEnemyDamage();

    // Test case to test player damage
    void testPlayerDamage();

    // Test case to test player health bar
    void testPlayerHealthBar();

    // Test case for bullet constructor
    void testBulletConstructor();

    // Test case for spawn handler
    void testSpawnHandler();

    // Constructor
    TestCases();

    // Run all tests function
    void runAllTests();


};


#endif //RUNNINGDEAD_TESTCASES_H
