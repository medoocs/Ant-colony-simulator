#pragma once
#include <SFML/Graphics.hpp>

#define rad2deg (360 / (M_PI * 2))

class Mrav{
    private:
        sf::Texture tMrav;
        sf::Vector2f position, velocity, desiredDirection;
        bool flag = true;

	public:
        sf::Sprite sMrav;
        Mrav();
        ~Mrav() = default;
        void move(sf::Time dt, sf::RenderWindow& window);
        sf::Sprite getSprite();
        void foundFood()
};