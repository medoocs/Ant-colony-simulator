#include "food.h"
#include <iostream>

Food::Food(sf::Vector2f pos) {
	position = pos;
    std::cout << position.x << "  " << position.y << std::endl;
    amount = 10.f;
    if (!tFood.loadFromFile("res/circle.png"))
        std::cout << "Error nema slike" << std::endl;

    tFood.setSmooth(true);
    sFood.setTexture(tFood);
    sFood.setOrigin(pos);
    sFood.setScale(0.025f, 0.025f);
    sFood.setColor(sf::Color(0, 255, 0));
    sFood.setPosition(pos);
}

void Food::eat() {
    amount -= 1.f;
}

bool Food::isGone() {
    if (amount <= 0.f)
        return true;
    else return false;
}

sf::Sprite Food::getSprite() {
    return sFood;
}