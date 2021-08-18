#pragma once
#include <SFML/Graphics.hpp>

class Marker {
	private:
		bool isBlack;
	public:
		sf::Texture tMarker;
		sf::Sprite sMarker;
		Marker(sf::Vector2f position);
		~Marker() = default;
		void changeColor();
		void changeToDefault();
		sf::Sprite getSprite();
		bool getBlack();
		void setBlack(bool set);
};
