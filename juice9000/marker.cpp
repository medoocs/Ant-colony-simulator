#include <SFML/Graphics.hpp>
#include "marker.h"
#include "config.hpp"
#include <iostream>

Marker::Marker(sf::Vector2f position) {
    isBlack = false;
    sMarker.setTexture(*Config::tMarker);
    sMarker.setOrigin((*Config::tMarker).getSize().x / 2, (*Config::tMarker).getSize().y / 2);
    sMarker.setScale(0.05f, 0.05f);
    sMarker.setColor(sf::Color::White);
    sMarker.setPosition(position.x, position.y);
}

void Marker::changeColor() {
    sMarker.setColor(sf::Color::Black);
}

void Marker::changeToDefault() {
    sMarker.setColor(sf::Color::White);
}

sf::Sprite Marker::getSprite() {
    return sMarker;
}

bool Marker::getBlack() {
    return isBlack;
}

void Marker::setBlack(bool set) {
    isBlack = set;
    //std::cout << set << "\n";
}