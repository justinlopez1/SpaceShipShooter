//
// Created by funny on 4/24/2023.
//

#include "enemybullet.h"

enemy1bullet::enemy1bullet(textures *texturesptr, sf::Vector2f position, std::string t) {
    type = std::move(t);
    bulletsprite.setTexture(*texturesptr->gettexture("enemy1bullet"));
    bulletsprite.setOrigin(bulletsprite.getLocalBounds().width/2, bulletsprite.getLocalBounds().height/2);
    bulletsprite.scale(1, 1);
    bulletsprite.setPosition(position.x, position.y + 50);

    xvelocity = 0;
    yvelocity = 700;

    bullethitbox.setSize(sf::Vector2f(bulletsprite.getLocalBounds().width/2, bulletsprite.getLocalBounds().height/2));
    bullethitbox.setOrigin(bullethitbox.getLocalBounds().width/2, bullethitbox.getLocalBounds().height/2);
    bullethitbox.setPosition(bulletsprite.getPosition());
    bullethitbox.setFillColor(sf::Color::White);
}

void enemy1bullet::move(sf::Time dt) {
    bulletsprite.move(0, yvelocity * dt.asSeconds());
    bullethitbox.setPosition(bulletsprite.getPosition());
}

sf::Sprite *enemy1bullet::getbulletsprite() {
    return &bulletsprite;
}

sf::RectangleShape *enemy1bullet::getbullethitbox() {
    return &bullethitbox;
}


