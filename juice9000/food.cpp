#include "food.h"
#include <iostream>
#include "config.hpp"

Food::Food(sf::Vector2f pos) {
	position = pos;
    //std::cout << position.x << "  " << position.y << std::endl;
    amount = 100;
    circle.setRadius(10.0f);
    circle.setOrigin(10.0f, 10.0f);
    circle.setFillColor(Config::cFood);
    circle.setPosition(pos);

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

sf::CircleShape Food::getSprite() {
    return circle;
}
