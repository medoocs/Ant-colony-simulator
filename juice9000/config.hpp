#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

struct Config {
	static sf::Color cAnt;
	static sf::Color cFood;
	static sf::Color cMravinjak;

	static uint32_t width;
	static uint32_t height;

	static std::shared_ptr<sf::Texture> tAnt;
	static std::shared_ptr<sf::Texture> tFood;
	static std::shared_ptr<sf::Texture> tMarker;

	static void loadTextures();
	static void freeTextures();

};