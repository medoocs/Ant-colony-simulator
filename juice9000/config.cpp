#include <SFML/Graphics.hpp>
#include "config.h"

sf::Color Config::cAnt = sf::Color(255, 73, 68);
sf::Color Config::cFood = sf::Color::Magenta;
sf::Color Config::cMravinjak = sf::Color(181, 101, 29);

std::shared_ptr<sf::Texture> Config::tAnt;
std::shared_ptr<sf::Texture> Config::tMarker;
std::shared_ptr<sf::Texture> Config::tFood;

void Config::loadTextures() {
	tAnt = std::make_shared<sf::Texture>();
	tAnt->loadFromFile("res/ant_2.png");
	tAnt->setSmooth(true);

	tFood = std::make_shared<sf::Texture>();
	tFood->loadFromFile("res/circle.png");
	tFood->setSmooth(true);

	tMarker = std::make_shared<sf::Texture>();
	tMarker->loadFromFile("res/marker.png");
	tMarker->setSmooth(true);
}

void Config::freeTextures() {
	tAnt = nullptr;
	tMarker = nullptr;
	tFood = nullptr;
}