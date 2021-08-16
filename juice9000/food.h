#pragma once
#include <SFML/Graphics.hpp>
class Food {
	public:
		sf::Vector2f position;
		sf::Texture tFood;
		sf::Sprite sFood;
		float amount;

		Food(sf::Vector2f pos);
		~Food() = default;
		void eat();
		bool isGone();
		sf::Sprite getSprite();
};