//
// Created by funny on 4/16/2023.
//

#ifndef GALAGAGAME_PLAYERSHIP_H
#define GALAGAGAME_PLAYERSHIP_H

#include <SFML/graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <random>
#include "textures.h"
#include "background.h"
#include "enemy.h"
#include "enemybullet.h"




class playership {
    bool alive = true;
    const float velocity = 300;
    int score = 0;
    std::mt19937 generator;

    sf::Font font;

    sf::Sprite playersprite;
    textures* texturemanager;
    sf::Text scoretext;

    struct playerbullet {
        float velocity = 800;
        sf::RectangleShape bullethitbox;
        sf::Sprite bulletsprite;

        playerbullet(textures* texturesptr, sf::Vector2f position);
        void move(sf::Time dt);
        sf::Sprite* getbulletsprite();
        sf::RectangleShape* getbullethitbox();
        sf::Vector2f getbulletposition();
    };

    std::vector<playerbullet*> bulletvect;
    std::vector<enemy*> enemyvect;
    std::vector<enemybullet*> enemybulletvect;

    


public:
    ~playership();
    int getrandom(int min, int max);
    explicit playership(textures* texturesptr);

    void updateship(sf::Time dt);
    void updateenemies(sf::Time dt);
    void playerbulletenemycollisioncheck();
    void enemyplayercollisioncheck();

    void addenemy(sf::Clock &timer);
    void addasteroid(sf::Clock &timer);

    void checkoutofbounds();
    void addplayerbullet();
    void drawall(sf::RenderWindow &window);
    void updatescore(sf::RenderWindow &window);



};


#endif //GALAGAGAME_PLAYERSHIP_H
