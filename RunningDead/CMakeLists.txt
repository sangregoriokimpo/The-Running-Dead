cmake_minimum_required(VERSION 3.14)
project(RunningDead)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Enemy.h
        Entity.h
        Player.h
        SpawnHandler.h
        ShootingSystemV2.h
        TestCases.cpp
        TestCases.h
        BulletV2.cpp
        Enemy.cpp
        Entity.cpp
        Player.cpp
        ShootingSystemV2.cpp
        SpawnHandler.cpp)
add_executable(RunningDead ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(RunningDead sfml-system sfml-window sfml-graphics sfml-audio sfml-network)