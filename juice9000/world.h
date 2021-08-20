#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
class World {
	public:
		// toHome i toFood feromon grid 
		static float homeMatrix[Config::width][Config::height], foodMatrix[Config::width][Config::height];
		// odabir smjera ovisno o koncentraciji feromona u gridu
		static int chooseDirection(sf::Vector2f &positionMrava, float angleMrav, sf::RenderWindow& window, bool foundFood);
		// increment grid home
		static void incHome(sf::Vector2i pos);
		// increment grid food
		static void incFood(sf::Vector2i pos);
		// decrement grid home
		static void decHome(sf::Vector2i pos);
		// decrement grid food
		static void decFood(sf::Vector2i pos);
};