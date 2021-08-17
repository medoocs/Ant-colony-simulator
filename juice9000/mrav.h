#pragma once
#include <SFML/Graphics.hpp>
#include "food.h"
#define rad2deg (360 / (M_PI * 2))

class Mrav{
    private:
        sf::Texture tMrav;
        sf::Vector2f position, velocity, desiredDirection;
        bool flag = true, hasFood = false;

	public:
        sf::Sprite sMrav;
        Mrav();
        ~Mrav() = default;
        void move(sf::Time dt, sf::RenderWindow& window, std::vector<Food>& hrana);
        sf::Sprite getSprite();
        void checkFood(std::vector<Food>& hrana);
};