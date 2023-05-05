//
// Created by funny on 4/18/2023.
//

#include "enemy.h"
#include <random>
#include <iostream>
#include <chrono>
using namespace std;


enemy1::enemy1(textures* t, sf::Vector2f pos) : enemy(){
    enemysprite.setTexture(*t->gettexture("enemy1"));
    enemysprite.setOrigin(enemysprite.getLocalBounds().width/2, enemysprite.getLocalBounds().height/2);
    enemysprite.setPosition(pos);


    enemyhitbox.setSize(sf::Vector2f(enemysprite.getLocalBounds().width/2, enemysprite.getLocalBounds().height/2));
    enemyhitbox.setOrigin(enemyhitbox.getLocalBounds().width/2, enemyhitbox.getLocalBounds().height/2);
    enemyhitbox.setPosition(enemysprite.getPosition());
    enemyhitbox.setFillColor(sf::Color::White);

}

void enemy1::updateposition(sf::Time dt) {
    enemysprite.move(float(xvelocity) * dt.asSeconds(), float(yvelocity) * dt.asSeconds());
    enemyhitbox.setPosition(enemysprite.getPosition());

}

sf::Sprite *enemy1::getsprite() {
    return &enemysprite;
}

sf::RectangleShape* enemy1::getrect() {
    return &enemyhitbox;
}

int enemy1::gethealth() {
    return health;
}

void enemy1::hit() {
    health -=1;
}

sf::Clock *enemy1::getclock() {
    return &shoottimer;
}

asteroid::asteroid(textures *t, sf::Vector2f pos, sf::Vector2f vel, int size) {
    xvelocity = int(vel.x);
    yvelocity = int(vel.y);

    if (size == 0) {
        enemysprite.setTexture(*t->gettexture("asteroidsmall"));
        health = 1;
    }

    if (size == 1) {
        enemysprite.setTexture(*t->gettexture("asteroidmedium"));
        health = 2;
    }

    if (size == 2) {
        enemysprite.setTexture(*t->gettexture("asteroidlarge"));
        health = 3;
    }

    enemysprite.setOrigin(enemysprite.getLocalBounds().width/2, enemysprite.getLocalBounds().height/2);
    enemysprite.setPosition(pos);


    enemyhitbox.setSize(sf::Vector2f(enemysprite.getLocalBounds().width/1.3, enemysprite.getLocalBounds().height/1.8));
    enemyhitbox.setOrigin(enemyhitbox.getLocalBounds().width/2, enemyhitbox.getLocalBounds().height/2);
    enemyhitbox.setPosition(enemysprite.getPosition());
    enemyhitbox.setFillColor(sf::Color::White);
}

void asteroid::updateposition(sf::Time dt) {
    enemysprite.move(xvelocity * dt.asSeconds(), yvelocity * dt.asSeconds());
    enemyhitbox.setPosition(enemysprite.getPosition());
}

sf::Sprite *asteroid::getsprite() {
    return &enemysprite;
}

sf::RectangleShape *asteroid::getrect() {
    return &enemyhitbox;
}

int asteroid::gethealth() {
    return health;
}

void asteroid::hit() {
    health -= 1;

    if (health == 0 or health >=3)
        return;

    else if (health == 2)
        enemysprite.setColor(sf::Color(255, 200, 200));

    else if (health == 1)
        enemysprite.setColor(sf::Color(255, 150, 150));

}

sf::Clock *asteroid::getclock() {
    return nullptr;
}

enemy2::enemy2(textures *t, sf::Vector2f pos) : enemy() {
    enemysprite.setTexture(*t->gettexture("enemy2"));
    enemysprite.setOrigin(enemysprite.getLocalBounds().width/2, enemysprite.getLocalBounds().height/2);
    enemysprite.setPosition(pos);


    enemyhitbox.setSize(sf::Vector2f(enemysprite.getLocalBounds().width/2, enemysprite.getLocalBounds().height/2));
    enemyhitbox.setOrigin(enemyhitbox.getLocalBounds().width/2, enemyhitbox.getLocalBounds().height/2);
    enemyhitbox.setPosition(enemysprite.getPosition());
    enemyhitbox.setFillColor(sf::Color::White);
}

void enemy2::updateposition(sf::Time dt) {
    enemysprite.move(float(xvelocity) * dt.asSeconds(), float(yvelocity) * dt.asSeconds());
    enemyhitbox.setPosition(enemysprite.getPosition());
}

sf::Sprite *enemy2::getsprite() {
    return &enemysprite;
}

sf::RectangleShape *enemy2::getrect() {
    return &enemyhitbox;
}

int enemy2::gethealth() {
    return health;
}

void enemy2::hit() {
    health -= 1;
    enemysprite.setColor(sf::Color(255, 150, 150));
}

sf::Clock *enemy2::getclock() {
    return &shoottimer;
}
