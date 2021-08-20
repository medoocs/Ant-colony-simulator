#pragma once
#include <SFML/Graphics.hpp>
class Food {
	private:
		sf::CircleShape circle;
		sf::Vector2f position;
		sf::Texture tFood;
		sf::Sprite sFood;
		int32_t amount;
	public:
		// konstruktor za sprite i varijable
		Food(sf::Vector2f pos);
		~Food() = default;
		// oduzmi amount
		void eat();
		// provjeri jel food prazan
		bool isGone() const;
		// return amount
		int32_t getAmount();
		// return sprite
		sf::CircleShape getSprite();
};