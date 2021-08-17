#pragma once
#include <SFML/Graphics.hpp>
class Food {
	public:
		sf::Vector2f position;
		sf::Texture tFood;
		sf::Sprite sFood;
		int32_t amount;

		Food(sf::Vector2f pos);
		~Food() = default;
		void eat();
		bool isGone() const;
		sf::Sprite getSprite();
};