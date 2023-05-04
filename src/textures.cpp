//
// Created by funny on 4/16/2023.
//

#include "textures.h"
#include <iostream>
using namespace std;

textures::textures(const std::vector<std::string> &imagenames) {
    for (const auto & imagename : imagenames) {
        sf::Texture t;
        t.loadFromFile(imagename);
        string temp = imagename.substr(13, imagename.size() - 17);
        texturemap.emplace(temp, t);
    }
}

sf::Texture *textures::gettexture(const std::string &texturename) {
    sf::Texture* newptr = &texturemap[texturename];
    return newptr;
}
