//
// Created by funny on 4/18/2023.
//

#ifndef GALAGAGAME_BACKGROUND_H
#define GALAGAGAME_BACKGROUND_H
#include <SFML/graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "textures.h"
#define WIDTH 1400
#define HEIGHT 900
#define PI 3.14159265358979323846

class background {
    textures* texturemanager;
    std::vector<sf::Sprite> backgroundspritesvect;
    float velocity = 75;
    int current;

public:
    explicit background(textures* t);
    void updatebackground(sf::RenderWindow &window, sf::Time dt, bool update);
};


#endif //GALAGAGAME_BACKGROUND_H
