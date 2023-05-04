//
// Created by funny on 4/16/2023.
//

#include "playership.h"
#include <chrono>
#include <random>
#include <utility>
using namespace std;

playership::playership(textures* texturesptr) {
    alive = true;
    playersprite.setTexture(*texturesptr->gettexture("spaceship"));
    playersprite.setScale(.8, .8);
    playersprite.setOrigin(playersprite.getLocalBounds().width/2, playersprite.getLocalBounds().height/2);
    playersprite.setPosition(float(WIDTH)/2, float(HEIGHT)/2 + 300);
    texturemanager = texturesptr;


    generator.seed(chrono::steady_clock::now().time_since_epoch().count());

}

void playership::updateship(sf::Time dt) {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) or
    sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) and
    playersprite.getPosition().x - playersprite.getLocalBounds().width/4 > 0) {
        playersprite.move(-velocity * dt.asSeconds(), 0);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) or
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) and
        playersprite.getPosition().x + playersprite.getLocalBounds().width/4 < WIDTH) {
        playersprite.move(velocity * dt.asSeconds(), 0);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) or
         sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) and
        playersprite.getPosition().y - playersprite.getLocalBounds().height/4 > 0) {
        playersprite.move(0, -velocity * dt.asSeconds());
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) or
         sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) and
        playersprite.getPosition().y + playersprite.getLocalBounds().height/4 < HEIGHT) {
        playersprite.move(0, velocity * dt.asSeconds());
    }
    for (int i = 0; i < bulletvect.size(); i++) {
        bulletvect[i]->move(dt);
        if (bulletvect[i]->getbulletposition().y <= 0) {
            delete bulletvect[i];
            bulletvect.erase(bulletvect.begin() + i);
        }
    }

}

void playership::addbullet() {
    bulletvect.emplace_back(new playerbullet(texturemanager, playersprite.getPosition()));
}

void playership::addenemy(sf::Clock &timer) {

    if (timer.getElapsedTime().asSeconds() < 6)
        return;

    int temp = getrandom(1, 1);

    if (temp == 1)
    {
        int temp = getrandom(200, 1200);

        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp, 0)));
        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp - 35, -35)));
        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp + 35, -35)));
        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp - 70, -70)));
        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp + 70, -70)));
    }

    timer.restart();
}

void playership::updateenemies(sf::Time dt) {
    for (int i = 0; i < enemyvect.size(); i++) {
        enemyvect[i]->updateposition(dt);

        if (dynamic_cast<enemy1*>(enemyvect[i]) != nullptr) {
            //is enemy1 
            if (enemyvect[i]->getclock()->getElapsedTime().asSeconds() > 1.2) {
                enemybulletvect.push_back(new enemy1bullet(texturemanager, enemyvect[i]->getsprite()->getPosition(), "1"));
                enemyvect[i]->getclock()->restart();
            }
        }

        if (enemyvect[i]->getrect()->getPosition().y + 50 > HEIGHT) {
            delete enemyvect[i];
            enemyvect.erase(enemyvect.begin() + i);
        }
    }

    for (int i = 0; i < enemybulletvect.size(); i++) {
        enemybulletvect[i]->move(dt);
        if (enemybulletvect[i]->getbullethitbox()->getPosition().y + 50 > HEIGHT) {
            delete enemybulletvect[i];
            enemybulletvect.erase(enemybulletvect.begin() + i);
        }
    }


}

void playership::drawall(sf::RenderWindow &window) {
    for (auto & i : bulletvect) {
        window.draw(*i->getbulletsprite());
        //window.draw(*bulletvect[i]->getbullethitbox()); //hitbox drawing
    }

    for (auto & i : enemyvect) {
        window.draw(*i->getsprite());
        //window.draw(*enemyvect[i]->getrect());   //hitbox drawing
    }

    for (auto & i : enemybulletvect) {
        window.draw(*i->getbulletsprite());
        //window.draw(*enemybulletvect[i]->getbullethitbox());
    }

    window.draw(playersprite);

}

void playership::playerbulletenemycollisioncheck() {
    for (int i = 0; i < bulletvect.size(); i++) {
        for (auto & j : enemyvect) {
            if (bulletvect[i]->getbullethitbox()->getGlobalBounds().intersects(j->getrect()->getGlobalBounds())) {
                delete bulletvect[i];
                bulletvect.erase(bulletvect.begin() + i);
                j->hit();

            }

        }
    }

    for (int j = 0; j < enemyvect.size(); j++) {
        if (enemyvect[j]->gethealth() <= 0) {
            delete enemyvect[j];
            enemyvect.erase(enemyvect.begin() + j);

        }
    }
}

int playership::getrandom(int min, int max) {
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void playership::addasteroid(sf::Clock &timer) {

    if (timer.getElapsedTime().asSeconds() < 2.5)
        return;

    sf::Vector2f tempindex(getrandom(200, 1200), 0);
    sf::Vector2f tempvel(getrandom(-150, 150), getrandom(150, 450));
    int size = getrandom(0, 2);
    enemyvect.push_back(new asteroid(texturemanager, tempindex, tempvel, size));

    timer.restart();
}

void playership::deleteall() {
    for (auto i : bulletvect) {
        delete i;
    }
    for (auto i : enemyvect) {
        delete i;
    }
    for (auto i : enemybulletvect) {
        delete i;
    }
}


playership::playerbullet::playerbullet(textures *texturesptr, sf::Vector2f position) {
    bulletsprite.setTexture(*texturesptr->gettexture("bullet"));
    bulletsprite.setOrigin(bulletsprite.getLocalBounds().width/2, bulletsprite.getLocalBounds().height/2);
    bulletsprite.scale(1, 1);
    bulletsprite.setPosition(position);

    bullethitbox.setSize(sf::Vector2f(bulletsprite.getLocalBounds().width/2, bulletsprite.getLocalBounds().height/2));
    bullethitbox.setOrigin(bullethitbox.getLocalBounds().width/2, bullethitbox.getLocalBounds().height/2);
    bullethitbox.setPosition(bulletsprite.getPosition());
    bullethitbox.setFillColor(sf::Color::White);
}

void playership::playerbullet::move(sf::Time dt) {
    bulletsprite.move(0, velocity * dt.asSeconds());
    bullethitbox.setPosition(bulletsprite.getPosition());
}

sf::Sprite *playership::playerbullet::getbulletsprite() {
    return &bulletsprite;
}

sf::Vector2f playership::playerbullet::getbulletposition() {
    return bulletsprite.getPosition();
}

sf::RectangleShape* playership::playerbullet::getbullethitbox() {
    return &bullethitbox;
}

