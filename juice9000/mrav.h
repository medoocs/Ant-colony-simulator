#pragma once
#include <SFML/Graphics.hpp>
#include "food.h"
#include <vector>

class Mrav{
    private:
        uint32_t id;
        sf::Texture tMrav;
        sf::Vector2f position, velocity, desiredDirection;
        bool flag = true, foundFood = false, foundHome = false;
        sf::Sprite sMrav;
	public:
        // konstruktor za napravit sprite i settat varijable 
        Mrav(uint32_t idM);
        ~Mrav() = default;
        // funkcija za micanje mrava
        void move(sf::Time dt, sf::RenderWindow& window, std::vector<Food>& hrana, std::vector<Mrav>& mravi, int &pojeli);
        // vraca sprite
        sf::Sprite getSprite();
        // kolizija sa food
        void checkFood(std::vector<Food>& hrana);
        // kolizija za home
        void checkHome(int &pojeli);
};