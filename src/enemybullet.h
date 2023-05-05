//
// Created by funny on 4/24/2023.
//

#ifndef GALAGAGAME_ENEMYBULLET_H
#define GALAGAGAME_ENEMYBULLET_H
#include <SFML/graphics.hpp>
#include <SFML/Window.hpp>
#include "textures.h"
#include <iostream>

class enemybullet {

public:
    virtual void move(sf::Time dt) = 0;
    virtual sf::Drawable* getbulletsprite() = 0;
    virtual sf::RectangleShape* getbullethitbox() = 0;
    virtual ~enemybullet() {
        //std::cout << "enemybullet deleted" << std::endl;
    }
};


class enemy1bullet : virtual public enemybullet {
    float xvelocity = 0;
    float yvelocity = 0;
    sf::RectangleShape bullethitbox;
    sf::Sprite bulletsprite;
    std::string type;

public:
    enemy1bullet(textures* texturesptr, sf::Vector2f position, std::string t);
    void move(sf::Time dt) override;
    sf::Sprite* getbulletsprite() override;
    sf::RectangleShape* getbullethitbox() override;

};

class enemy2bullet : virtual public enemybullet {
    float xvelocity = 0;
    float yvelocity = 0;
    sf::CircleShape bulletcircle;
    sf::RectangleShape bullethitbox;
    std::string type;

public:
    enemy2bullet(textures* texturesptr, sf::Vector2f position, std::string t, sf::Vector2f velocity);
    void move(sf::Time dt) override;
    sf::CircleShape* getbulletsprite() override;
    sf::RectangleShape* getbullethitbox() override;

};

#endif //GALAGAGAME_ENEMYBULLET_H
