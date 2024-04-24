cmake_minimum_required(VERSION 3.26)
project(PA9_SFML_Workspace)

set(CMAKE_CXX_STANDARD 23)

add_executable(PA9_SFML_Workspace main.cpp
        MainMenu.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)
include_directories(c:/paResources)
target_link_libraries(PA9_SFML_Workspace sfml-system sfml-window sfml-graphics sfml-audio)

