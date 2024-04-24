//
// Created by gunna on 4/16/2024.
//
#ifndef PA9_SFML_WORKSPACE_MAINMENU_H
#define PA9_SFML_WORKSPACE_MAINMENU_H

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

using sf::RenderWindow;
using sf::Color;
using sf::Text;
using sf::Font;
using sf::VideoMode;
using sf::Event;
using sf::Keyboard;

#define MenuSize 2

class Menu {

private:

    int selected;
    Font font;
    Color menuRed;
    Color menuWhite;

public:

    Text mainMenu[MenuSize];

    Menu(float width, float height)
    {
        font.loadFromFile("c:/paResources/fonts/Blacklisted.ttf");

        menuRed = Color{200, 0, 0};
        menuWhite = Color{160,160,160};

        //Font titleFont;
        //titleFont.loadFromFile("c:/paResources/fonts/drGlitch.otf");

        //Play Option
        mainMenu[0].setFont(font);
        mainMenu[0].setFillColor(menuRed);
        mainMenu[0].setString("PLAY");
        mainMenu[0].setCharacterSize(90);
        mainMenu[0].setPosition(sf::Vector2f(50, 425));

        //Exit
        mainMenu[1].setFont(font);
        mainMenu[1].setFillColor(menuWhite);
        mainMenu[1].setString("EXIT");
        mainMenu[1].setCharacterSize(90);
        mainMenu[1].setPosition(sf::Vector2f(50, 575));

        selected = 0;
    }

    void draw(RenderWindow& window)
    {
        for (int i = 0; i < MenuSize; i++)
        {
            window.draw(mainMenu[i]);
        }
    }

    void moveUp()
    {
        if (selected - 1 >= -1) // not play
        {
            mainMenu[selected].setFillColor(menuWhite);
            selected--;

            if(selected == -1)
            {
                selected = MenuSize - 1;
            }

            mainMenu[selected].setFillColor(menuRed);
        }
    }

    void moveDown()
    {
        if (selected + 1 <= MenuSize) // not exit
        {
            mainMenu[selected].setFillColor(menuWhite);
            selected++;

            if (selected == MenuSize)
            {
                selected = 0;
            }

            mainMenu[selected].setFillColor(menuRed);
        }

    }

    void setSelected(int n) { selected = n; }

    int pressed() const { return selected; }

    ~Menu()
    {
        //destructor
    }

    void runMenu() {
        int page = 1000;
        /* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- *
         *      page      |     Function     *
         * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= *
         *      1000      |     Main Menu    *
         *      -1        |       close      *
         *       0        |     Play Game    *
         * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

        RenderWindow window(VideoMode(1000, 800), "RUNNING_DEAD");
        Menu menu(1000, 800);

        Text title;
        Font titleFont;
        titleFont.loadFromFile("c:/paResources/fonts/drGlitch.otf");

        title.setFont(titleFont);
        title.setFillColor(Color{200, 0, 0});
        title.setString("THE_RUNNING\nDEAD");
        title.setCharacterSize(102);
        title.setPosition(sf::Vector2f(50, 85));

        sf::Texture menuBG;
        menuBG.loadFromFile("c:/paResources/images/menuBG.jpg");
        sf::Sprite background;
        background.setTexture(menuBG);


        while (true)
        {
            if (page == 1000) {
                while (window.isOpen()) {
                    Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == Event::Closed) {
                            window.close();
                            break;
                        }
                        if (event.type == Event::KeyPressed) {
                            if (event.key.code == Keyboard::Up) {
                                menu.moveUp();
                            }
                            if (event.key.code == Keyboard::Down) {
                                menu.moveDown();
                            }
                            if (event.key.code == Keyboard::Return) { //user selects menu option
                                if (menu.pressed() == 0) { //Play Game
                                    page = 0;
                                }
                                if (menu.pressed() == 1) { //Close Program
                                    page = -1;
                                }
                            }
                        }
                    }
                    window.clear();
                    if (page != 1000) { //user no longer on menu
                        break;
                    }
                    window.draw(background);
                    window.draw(title);
                    menu.draw(window);
                    window.display();
                }

                if (page == -1) {
                    window.close();
                    cout << "Closing Menu" << endl;
                    break;
                }
                if (page == 0) {
                    //Play Game
                    cout << "Playing Game" << endl;
                    break;
                }
            }
        }
    }

};

//void runMenu();

#endif //PA9_SFML_WORKSPACE_MAINMENU_H
