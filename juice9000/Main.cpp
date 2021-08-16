#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include "mrav.h"
#include "food.h"

template<typename T>
void draw(std::vector<T>& shapes, sf::RenderWindow& window) {
    for (auto s : shapes) {
        window.draw(s.getSprite());
    }
}


int main()
{
    //init
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mravi9000");
    window.setFramerateLimit(144);
    
    std::vector<Mrav> mravi;
    std::vector<Food> hrana;
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
        mravi.emplace_back();
    }
        

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right){
                    sf::Vector2f mousePosition((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
                    //std::cout << mousePosition.x << "  " << mousePosition.y << std::endl;
                    hrana.emplace_back(mousePosition);
                }
                break;
            }
        }

        //clear
        window.clear(sf::Color(49, 99, 0));
        
        //moving
        for (int i = 0; i < n; ++i) {
            mravi[i].move(dt, window);
        }

        draw(hrana, window);
        draw(mravi, window);
        
        //display
        window.draw(sMravinjak);
        window.display();
    }

    return 0;
}