//
// Created by funny on 4/18/2023.
//

#ifndef GALAGAGAME_ENEMY_H
#define GALAGAGAME_ENEMY_H
#include "background.h"
#include <iostream>

class enemy {

public:
    virtual void updateposition(sf::Time dt) = 0;
    virtual sf::Sprite* getsprite() = 0;
    virtual sf::RectangleShape* getrect() = 0;
    virtual int gethealth() = 0;
    virtual void hit() = 0;
    virtual sf::Clock* getclock() = 0;


    virtual ~enemy() {
        //std::cout << "enemy deleted!" << std::endl;
    }
};


class enemy1 : virtual public enemy {
    int xvelocity = 0;
    int yvelocity = 150;
    int health = 1;
    sf::Sprite enemysprite;
    sf::RectangleShape enemyhitbox;
    sf::Clock shoottimer;

public:
    explicit enemy1(textures* t, sf::Vector2f pos);
    void updateposition(sf::Time dt) override;
    sf::Sprite* getsprite() override;
    sf::RectangleShape* getrect() override;
    int gethealth() override;
    void hit() override;
    sf::Clock* getclock() override;


};



class enemy2 : virtual public enemy {
    int xvelocity = 0;
    int yvelocity = 75;
    int health = 1;
    sf::Sprite enemysprite;
    sf::RectangleShape enemyhitbox;
    sf::Clock shoottimer;

public:
    explicit enemy2(textures* t, sf::Vector2f pos);
    void updateposition(sf::Time dt) override;
    sf::Sprite* getsprite() override;
    sf::RectangleShape* getrect() override;
    int gethealth() override;
    void hit() override;
    sf::Clock* getclock() override;

};



class asteroid : virtual public enemy {
    int xvelocity;
    int yvelocity;
    int health;
    sf::Sprite enemysprite;
    sf::RectangleShape enemyhitbox;


public:
    explicit asteroid(textures* t, sf::Vector2f pos, sf::Vector2f vel, int size);
    void updateposition(sf::Time dt) override;
    sf::Sprite* getsprite() override;
    sf::RectangleShape* getrect() override;
    int gethealth() override;
    void hit() override;
    sf::Clock* getclock() override;


};

#endif //GALAGAGAME_ENEMY_H
