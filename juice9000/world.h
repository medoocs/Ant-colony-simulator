#pragma once
#include <SFML/Graphics.hpp>
class World {
	public:
		static float homeMatrix[1280][720], foodMatrix[1280][720];
		static int chooseHomeDirection(sf::Vector2f &positionMrava, float angleMrav, sf::RenderWindow& window);
		static int chooseFoodDirection(sf::Vector2f& positionMrava, float angleMrav, sf::RenderWindow& window);
		static void incHome(sf::Vector2i pos);
		static void incFood(sf::Vector2i pos);
		static void decHome(sf::Vector2i pos);
		static void decFood(sf::Vector2i pos);
};