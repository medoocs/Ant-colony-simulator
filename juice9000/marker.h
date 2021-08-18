#pragma once
#include <SFML/Graphics.hpp>

class Marker {
	public:
		sf::CircleShape sMarker;
		sf::Texture tMarker;
		Marker(sf::Vector2f position);
		~Marker() = default;
		void changeColor();
		void changeToDefault();
		sf::CircleShape getSprite();
};
