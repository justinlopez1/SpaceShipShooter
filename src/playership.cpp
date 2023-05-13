//
// Created by funny on 4/16/2023.
//

#include "playership.h"
#include <chrono>
#include <random>
#include <utility>
#include <math.h>
using namespace std;

playership::playership(textures* texturesptr) {
    alive = true;
    playersprite.setTexture(*texturesptr->gettexture("spaceship"));
    playersprite.setScale(.6, .6);
    playersprite.setOrigin(playersprite.getLocalBounds().width/2, playersprite.getLocalBounds().height/2);
    playersprite.setPosition(float(WIDTH)/2, float(HEIGHT)/2 + 300);
    texturemanager = texturesptr;

    if (!font.loadFromFile("files/font.ttf")) cout << "font load error" << endl;
    scoretext.setFont(font);
    scoretext.setString("000000");
    scoretext.setPosition(WIDTH - (scoretext.getLocalBounds().width), 0);

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

void playership::addplayerbullet() {
    bulletvect.emplace_back(new playerbullet(texturemanager, playersprite.getPosition()));
}

void playership::addenemy(sf::Clock &timer) {

    if (timer.getElapsedTime().asSeconds() < 3.5)
        return;

    int temp = getrandom(1, 3);

    if (temp == 1)
    {
        int temp_position = getrandom(200, 1200);

        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp_position, 0)));
        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp_position - 35, -35)));
        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp_position + 35, -35)));
        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp_position - 70, -70)));
        enemyvect.push_back(new enemy1(texturemanager, sf::Vector2f(temp_position + 70, -70)));
    }
    if (temp == 2) 
    {
        int temp_position = getrandom(100, 1100);
        enemyvect.push_back(new enemy2(texturemanager, sf::Vector2f(temp_position, 0)));
    }

    if (temp == 3)
    {
        int temp_position = getrandom(100, 1100);
        enemyvect.push_back(new satelite(texturemanager, sf::Vector2f(temp_position, 0)));
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

        if (dynamic_cast<enemy2*>(enemyvect[i]) != nullptr) {
            //is enemy2
            if (enemyvect[i]->getclock()->getElapsedTime().asSeconds() > 1.75) {
                for (int j = 0; j < 24; j++) {
                    float angle = j * PI / 12;
                    float xvelocity = cos(angle);
                    float yvelocity = sin(angle);
                    enemybulletvect.push_back(new enemy2bullet(texturemanager, enemyvect[i]->getrect()->getPosition(), "2", sf::Vector2f(xvelocity, yvelocity)));
                }
                
                enemyvect[i]->getclock()->restart();
            }
        }

        if (dynamic_cast<satelite*>(enemyvect[i]) != nullptr) {
            //is satelite
            int distancex = playersprite.getPosition().x - enemyvect[i]->getsprite()->getPosition().x;
            int distancey = playersprite.getPosition().y - enemyvect[i]->getsprite()->getPosition().y;
            float angle = atan2(distancey, distancex);
            enemyvect[i]->getsprite()->setRotation(angle * 180 / PI);
            enemyvect[i]->getrect()->setRotation(angle * 180 / PI);

            if (enemyvect[i]->getclock()->getElapsedTime().asSeconds() > 2) {
                int distancex = playersprite.getPosition().x - enemyvect[i]->getsprite()->getPosition().x;
                int distancey = playersprite.getPosition().y - enemyvect[i]->getsprite()->getPosition().y;
                float angle = atan2(distancey, distancex);

                enemybulletvect.push_back(new satelitebullet(texturemanager, enemyvect[i]->getsprite()->getPosition(), "3", sf::Vector2f(cos(angle), sin(angle)), angle * 180 / PI));

                enemyvect[i]->getsprite()->setRotation(angle * 180 / PI);

                enemyvect[i]->getclock()->restart();
            }
        }

    }

    for (int i = 0; i < enemybulletvect.size(); i++) {
        enemybulletvect[i]->move(dt);
    }

    checkoutofbounds();

}

void playership::drawall(sf::RenderWindow &window) {
    for (auto & i : bulletvect) {
        window.draw(*i->getbulletsprite());
        //window.draw(*bulletvect[i]->getbullethitbox()); //hitbox drawing
    }

    for (auto & i : enemybulletvect) {
        window.draw(*i->getbulletsprite());
        //window.draw(*i->getbullethitbox());
    }

    for (auto & i : enemyvect) {
        window.draw(*i->getsprite());
        //window.draw(*i->getrect());   //hitbox drawing
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

    for (int i = 0; i < enemyvect.size(); i++) {
        if (enemyvect[i]->gethealth() <= 0) {
            score += enemyvect[i]->getscore();
            delete enemyvect[i];
            enemyvect.erase(enemyvect.begin() + i);

        }
    }
}

int playership::getrandom(int min, int max) {
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void playership::addasteroid(sf::Clock &timer) {

    if (timer.getElapsedTime().asSeconds() < 1.2)
        return;

    int temp = getrandom(1, 3);
    if (temp == 1) {
        sf::Vector2f tempindex(getrandom(200, WIDTH - 200), 0);
        sf::Vector2f tempvel(getrandom(-250, 150), getrandom(150, 450));
        int size = getrandom(0, 2);
        enemyvect.push_back(new asteroid(texturemanager, tempindex, tempvel, size));
    }
    else if (temp == 2) {
        sf::Vector2f tempindex(WIDTH + 50, getrandom(100, HEIGHT - 100));
        sf::Vector2f tempvel(getrandom(-450, -150), getrandom(-150, 150));
        int size = getrandom(0, 2);
        enemyvect.push_back(new asteroid(texturemanager, tempindex, tempvel, size));
        
    }
    else if (temp == 3) {
        sf::Vector2f tempindex(-50, getrandom(100, HEIGHT - 100));
        sf::Vector2f tempvel(getrandom(150, 450), getrandom(-150, 150));
        int size = getrandom(0, 2);
        enemyvect.push_back(new asteroid(texturemanager, tempindex, tempvel, size));
        
    }

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

void playership::checkoutofbounds() {
    for (int i = 0; i < enemybulletvect.size(); i++) {
        if (enemybulletvect[i]->getbullethitbox()->getPosition().y > HEIGHT + 100 or enemybulletvect[i]->getbullethitbox()->getPosition().y < -100 or 
            enemybulletvect[i]->getbullethitbox()->getPosition().x < -100 or enemybulletvect[i]->getbullethitbox()->getPosition().x > WIDTH + 100) {
            delete enemybulletvect[i];
            enemybulletvect.erase(enemybulletvect.begin() + i);
        }
    }

    for (int i = 0; i < enemyvect.size(); i++) {
        if (enemyvect[i]->getrect()->getPosition().y > HEIGHT + 100 or enemyvect[i]->getrect()->getPosition().y < -100 or 
            enemyvect[i]->getrect()->getPosition().x < -100 or enemyvect[i]->getrect()->getPosition().x > WIDTH + 100) {
                    delete enemyvect[i];
                    enemyvect.erase(enemyvect.begin() + i);
            }
    }

}

void playership::updatescore(sf::RenderWindow &window) {
    string tempscorestring = to_string(score);
    if (tempscorestring.size() < 6) {
        for (int i = tempscorestring.size(); i < 6; i++) {
            tempscorestring = "0" + tempscorestring;
        }
    }


    scoretext.setString(tempscorestring);
    scoretext.setPosition(WIDTH - (scoretext.getLocalBounds().width + 100), 0);
    window.draw(scoretext);
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
    bulletsprite.move(0, -velocity * dt.asSeconds());
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

