#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include "mrav.h"

void draw(std::vector<Mrav>& mravi, sf::RenderWindow& window) {
    for (auto m : mravi) {
        window.draw(m.sMrav);
    }

    std::cout << "333" << std::endl;
}


int main()
{
    //init
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mravi9000");
    window.setFramerateLimit(144);
    
    std::vector<Mrav> mravi;
    int n = 5;

    //mravinjak
    sf::Texture tMravinjak;
    if (!tMravinjak.loadFromFile("res/marker.png"))
        return -1;
    tMravinjak.setSmooth(true);
    sf::Sprite sMravinjak;
    sMravinjak.setTexture(tMravinjak);
    sMravinjak.setScale(1.5f, 1.5f);
    sMravinjak.setColor(sf::Color(165, 42, 42));
    sMravinjak.setPosition(1280 / 2 - tMravinjak.getSize().x / 2 * 1.5f, 720 / 2 - tMravinjak.getSize().y / 2 * 1.5f);

    for (int i = 0; i < n; ++i) {
        Mrav newMrav;
        mravi.push_back(newMrav);
    }
        

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //clear
        window.clear(sf::Color(49, 99, 0));
        window.draw(sMravinjak);
        //moving
        for(auto m: mravi)
            m.move(dt, window);
        draw(mravi, window);
        //display
        window.display();
    }

    return 0;
}