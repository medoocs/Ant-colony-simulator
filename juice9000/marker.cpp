#include <SFML/Graphics.hpp>
#include "marker.h"
#include "config.hpp"
#include <iostream>

Marker::Marker(sf::Vector2f position) {
    sMarker.setRadius(0.25f);
    sMarker.setOrigin(0.25f, 0.25f);
    sMarker.setFillColor(sf::Color(255,255,255,0.1));
    sMarker.setPosition(position.x, position.y);
}

void Marker::changeColor() {
    sMarker.setFillColor(sf::Color::Black);
}

void Marker::changeToDefault() {
    sMarker.setFillColor(sf::Color::White);
}

sf::CircleShape Marker::getSprite() {
    return sMarker;
}



