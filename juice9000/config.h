#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

struct Config {
	// colors
	static sf::Color cAnt;
	static sf::Color cFood;
	static sf::Color cMravinjak;
	// duzina i sirina ekrana
	static constexpr uint32_t width = 1280;
	static constexpr uint32_t height = 720;
	// radius senzora mrava
	static constexpr float rad_mrav = 25.f;
	// max speed mrava
	static constexpr float maxSpeed = 50.f;
	// koliko jako RNG tjece na promijenu smjera kretanja
	static constexpr float wanderStrength = 0.5f;
	// jacina promjene smjera
	static constexpr float steerStrength = 50.f;
	// kolicina hrane u jednoj texturi
	static const int amount = 1000;
	// broj mrava
	static const int nMrav = 1024;
	// senzor feromon threshold
	static const int follow_force = 10;
	// radius mravinjaka
	static constexpr float rad_mravinjak = 30.f;
	// radius hrane
	static constexpr float rad_food = 10.f;
	// ako mu senzori kazu da ide lijevo, ici ce 20 stupnjeva u lijevo... i obrnuto
	static constexpr float deg_mrav = 20.f;
	// food feromon increment
	static constexpr float fInc = 0.5f;
	// food feromon decrement
	static constexpr float fDec = 0.0015f;
	// home feromon increment
	static constexpr float hInc = 0.5f;
	// home feromon decrement
	static constexpr float hDec = 0.0005f;
	// pointeri na texture spriteova
	static std::shared_ptr<sf::Texture> tAnt;
	static std::shared_ptr<sf::Texture> tFood;
	static std::shared_ptr<sf::Texture> tMarker;
	// load textures from files
	static void loadTextures();
	static void freeTextures();

};
