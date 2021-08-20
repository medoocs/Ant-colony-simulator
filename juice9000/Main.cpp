#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include "mrav.h"
#include "food.h"
#include "config.hpp"
#include <deque>
#include <ios>
#include <string> 
#include <sstream>
#include "world.h"


template<typename T>
void draw(std::vector<T>& shapes, sf::RenderWindow& window) {
    for (auto &s : shapes) {
        window.draw(s.getSprite());
    }
}

void drawMarkersFunc(sf::RenderWindow& window) {
    sf::Image tockice;
    tockice.create(1280, 720, sf::Color::Transparent);
    
    for (int i = 0; i < 1280; ++i) {
        for (int j = 0; j < 720; ++j) {
            if (World::homeMatrix[i][j] > 0) {
                tockice.setPixel(i, j, sf::Color(255,255,255,120));
                World::homeMatrix[i][j] -= 0.00015f;
                if (World::homeMatrix[i][j] < 0) World::homeMatrix[i][j] = 0;
            }
                
            if (World::foodMatrix[i][j] > 0) {
                tockice.setPixel(i, j, sf::Color::Black);
                World::foodMatrix[i][j] -= 0.0015f;
                if (World::foodMatrix[i][j] < 0) World::foodMatrix[i][j] = 0;
            }
        }
    }
    sf::Texture texture;
    texture.loadFromImage(tockice);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    window.draw(sprite);
}


int main()
{
    int pojeli = 0;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    //init
    //sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(Config::width, Config::height), "Mravi9000"/*, sf::Style::Default, settings*/);
    window.setFramerateLimit(144);
    
    Config::loadTextures();

    std::vector<Mrav> mravi;
    std::vector<Food> hrana;
    std::deque<Marker> markeri;

    int n = 1024;
    bool drawMarkers = true;
    //mravinjak
    sf::CircleShape sMravinjak(30.0f);
    sMravinjak.setOrigin(30.0f, 30.0f);
    sMravinjak.setFillColor(Config::cMravinjak);
    sMravinjak.setPosition(1280/2, 720/2);

    sf::Font font;
    if (!font.loadFromFile("C:\\WINDOWS\\FONTS\\ARIAL.TTF"))
    {
        std::cout << "can't load font" << std::endl;
    }

    
    sf::Text text("FARO", font);
    text.setCharacterSize(20);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(1280/2, 720/2);
    

    for (int i = 0; i < n; ++i) {
        mravi.emplace_back(i);
    }
        

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        World::foodMatrix[(int)1280 / 2][(int)720 / 2] = 10000;
        World::homeMatrix[(int)1280 / 2][(int)720 / 2] = 10000;
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
                    //std::cout << mousePosition.x << " clic " << mousePosition.y << std::endl;
                    hrana.emplace_back(mousePosition);
                }
                break;
            }
        }

        //clear
        window.clear(sf::Color(49, 99, 0));
        
        //moving
        for (int i = 0; i < n; ++i) {
            mravi[i].move(dt, window, hrana, mravi, drawMarkers, markeri, pojeli);
        }

        auto it = std::remove_if(hrana.begin(), hrana.end(), [](const auto& x) {return x.isGone(); });
        if (it != hrana.end()) hrana.erase(it);

        drawMarkersFunc(window);
        draw(hrana, window);
        draw(mravi, window);
        
        //display
        window.draw(sMravinjak);
        std::stringstream ss;
        ss << pojeli;
        text.setString(ss.str());
        ss.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}