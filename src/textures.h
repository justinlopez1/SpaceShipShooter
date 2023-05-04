//
// Created by funny on 4/16/2023.
//

#ifndef GALAGAGAME_TEXTURES_H
#define GALAGAGAME_TEXTURES_H
#include <SFML/graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <map>
#pragma once

class textures {
    std::map<std::string, sf::Texture> texturemap;

public:
    explicit textures(const std::vector<std::string> &imagenames);
    sf::Texture* gettexture(const std::string &texturename);

};


#endif //GALAGAGAME_TEXTURES_H
