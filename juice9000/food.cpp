// Warning	C26812	The enum type 'sf::PrimitiveType' is unscoped.Prefer 'enum class' over 'enum' (Enum.3).juice9000
#pragma warning(disable: 26812)
#include "food.h"
#include <iostream>
#include "config.h"
#include "world.h"

Food::Food(sf::Vector2f &pos) {
	position = pos;
    amount = Config::amount;
    circle.setRadius(Config::rad_food);
    circle.setOrigin(Config::rad_food, Config::rad_food);
    circle.setFillColor(Config::cFood);
    circle.setPosition(pos);
    setFood(pos);

}

void Food::setFood(sf::Vector2f &pos) {
    for (int i = (int)pos.x - Config::rad_food; i <= (int)pos.x + Config::rad_food; ++i) {
        for (int j = (int)pos.y - Config::rad_food; j <= (int)pos.y + Config::rad_food; ++j) {
            if ((((int)pos.x - i) * ((int)pos.x - i) + ((int)pos.y - j) * ((int)pos.y - j)) <= Config::rad_food * Config::rad_food) {
                World::foodMatrix[i][j] = 100000;
            }
        }
    }
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
