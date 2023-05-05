#include <iostream>
#include <SFML/graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "src/textures.h"
#include "src/playership.h"
#include "src/background.h"
#include "src/leaker.h"
using namespace std;


void debug(sf::RenderWindow &window, const string &s, sf::Font &font) {
    sf::Text text(s, font);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    window.draw(text);
}


int main()
{
    //window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(999);
    //font
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) cout << "font load error" << endl;
    //texture manager
    vector<string> filenamevect = {"files/images/spaceship.png", "files/images/bullet.png",
                                   "files/images/background1.png", "files/images/enemy1.png",
                                   "files/images/background2.png", "files/images/background0.png",
                                   "files/images/background3.png", "files/images/background4.png",
                                   "files/images/asteroidsmall.png", "files/images/asteroidmedium.png",
                                   "files/images/asteroidlarge.png", "files/images/enemy1bullet.png",
                                   "files/images/enemy2.png",};

    textures texturemanager(filenamevect);
    //background sprite
    background b(&texturemanager);

    //entity objects
    playership player(&texturemanager);
    //clocks
    sf::Clock dtclock;
    sf::Clock shootclock;
    sf::Clock enemyspawnclock;
    sf::Clock asteroidspawnclock;

    while (window.isOpen())
    {
        sf::Time dt = dtclock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    player.deleteall();
                    return 0;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space and
                    shootclock.getElapsedTime().asSeconds() > 0.15) {
                        player.addplayerbullet();
                        shootclock.restart();
                    }

            }
        }


        player.addenemy(enemyspawnclock);
        player.addasteroid(asteroidspawnclock);

        player.updateenemies(dt);
        player.updateship(dt);
        player.playerbulletenemycollisioncheck();

        window.clear();
        b.updatebackground(window, dt);
        player.drawall(window);
        debug(window, to_string(dt.asSeconds()), font);
        window.display();
    }
}
