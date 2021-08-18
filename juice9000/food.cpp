#include "food.h"
#include <iostream>
#include "config.hpp"

Food::Food(sf::Vector2f pos) {
	position = pos;
    //std::cout << position.x << "  " << position.y << std::endl;
    amount = 10;
    sFood.setTexture((*Config::tFood));
    sFood.setOrigin(position);
    sFood.setScale(0.05f, 0.05f);
    sFood.setColor(Config::cFood);
    sFood.setPosition(position.x, position.y);
}

void Food::eat() {
    amount--;
    std::cout << amount <<" JEDEM\n";
}

int32_t Food::getAmount() {
    return amount;
}

bool Food::isGone() const{
    if (amount <= 0)
        return true;
    else return false;
}

sf::Sprite Food::getSprite() {
    return sFood;
}
