//
// Created by funny on 4/18/2023.
//

#include "background.h"
#include <iostream>
using namespace std;

background::background(textures *t) {
    texturemanager = t;
    sf::Sprite s;
    s.setTexture(*texturemanager->gettexture("background0"));
    s.setPosition(0, -HEIGHT);
    backgroundspritesvect.push_back(s);

    sf::Sprite ss1;
    ss1.setTexture(*texturemanager->gettexture("background1"));
    ss1.setPosition(0, -2 * HEIGHT);
    backgroundspritesvect.push_back(ss1);

    backgroundspritesvect.push_back(s);

    sf::Sprite ss2;
    ss2.setTexture(*texturemanager->gettexture("background2"));
    ss2.setPosition(0, -2 * HEIGHT);
    backgroundspritesvect.push_back(ss2);

    backgroundspritesvect.push_back(s);

    sf::Sprite ss3;
    ss3.setTexture(*texturemanager->gettexture("background3"));
    ss3.setPosition(0, -2 * HEIGHT);
    backgroundspritesvect.push_back(ss3);

    backgroundspritesvect.push_back(s);

    sf::Sprite ss4;
    ss4.setTexture(*texturemanager->gettexture("background4"));
    ss4.setPosition(0, -2 * HEIGHT);
    backgroundspritesvect.push_back(ss4);

    current = 0;
}

void background::updatebackground(sf::RenderWindow &window, sf::Time dt) {
    int nextspriteindex = current + 1;
    if (current == backgroundspritesvect.size()-1)
        nextspriteindex = 0;

    backgroundspritesvect[current].move(0, velocity * dt.asSeconds());
    if (backgroundspritesvect[current].getPosition().y >= 0) {
        window.draw(backgroundspritesvect[nextspriteindex]);
        backgroundspritesvect[nextspriteindex].move(0, velocity * dt.asSeconds());
    }
    window.draw(backgroundspritesvect[current]);
    if (backgroundspritesvect[current].getPosition().y >= HEIGHT) {
        backgroundspritesvect[current].setPosition(0, -2 * HEIGHT);
        current += 1;
        if (current >= backgroundspritesvect.size())
            current = 0;
    }
}
