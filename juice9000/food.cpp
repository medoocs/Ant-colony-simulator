// Warning	C26812	The enum type 'sf::PrimitiveType' is unscoped.Prefer 'enum class' over 'enum' (Enum.3).juice9000
#pragma warning(disable: 26812)
#include "food.h"
#include <iostream>
#include "config.h"
#include "world.h"

Food::Food(sf::Vector2f pos) {
	position = pos;
    amount = Config::amount;
    circle.setRadius(Config::rad_food);
    circle.setOrigin(Config::rad_food, Config::rad_food);
    circle.setFillColor(Config::cFood);
    circle.setPosition(pos);
    World::foodMatrix[(int)pos.x][(int)pos.y] = 10000;

}

void Food::eat() {
    amount--;
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
