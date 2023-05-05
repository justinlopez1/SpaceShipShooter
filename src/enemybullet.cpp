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

enemy2bullet::enemy2bullet(textures *texturesptr, sf::Vector2f position, std::string t, sf::Vector2f velocity) {
    type = std::move(t);
    bulletcircle.setRadius(3);
    bulletcircle.setOrigin(bulletcircle.getLocalBounds().width/2, bulletcircle.getLocalBounds().height/2);
    bulletcircle.setPosition(position.x, position.y);
    

    xvelocity = velocity.y;
    yvelocity = velocity.x;

    
    bulletcircle.setOutlineThickness(1);
    bulletcircle.setOutlineColor(sf::Color::Black);
    bulletcircle.setFillColor(sf::Color(36, 255, 76));

    bullethitbox.setSize(sf::Vector2f(bulletcircle.getLocalBounds().width, bulletcircle.getLocalBounds().height));
    bullethitbox.setOrigin(bullethitbox.getLocalBounds().width/2, bullethitbox.getLocalBounds().height/2);
    bullethitbox.setPosition(bulletcircle.getPosition());
    bullethitbox.setFillColor(sf::Color::Yellow);

}

void enemy2bullet::move(sf::Time dt) {
    bulletcircle.move(xvelocity * dt.asSeconds(), yvelocity * dt.asSeconds());
    bullethitbox.setPosition(bulletcircle.getPosition());
}

sf::CircleShape *enemy2bullet::getbulletsprite() {
    return &bulletcircle;
}

sf::RectangleShape *enemy2bullet::getbullethitbox() {
    return &bullethitbox;
}




