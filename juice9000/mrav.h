#pragma once
#include <SFML/Graphics.hpp>
#include "food.h"
#include <vector>
#include "marker.h"
#include <deque>
#define rad2deg (360 / (M_PI * 2))

class Mrav{
    private:
        uint32_t id;
        sf::Texture tMrav;
        sf::Vector2f position, velocity, desiredDirection;
        std::vector<Marker> path;
        std::vector<sf::Vector2f> fullPositions;
        std::vector<float> angles;
        bool flag = true, foundFood = false, foundHome = false, prviFood = false, prviHome = false;
        int32_t steps = 0;


	public:
        sf::Sprite sMrav;
        Mrav(uint32_t idM);
        ~Mrav() = default;
        void move(sf::Time dt, sf::RenderWindow& window, std::vector<Food>& hrana, std::vector<Mrav>& mravi, bool drawMarkers, std::deque<Marker> &markeri, int &pojeli);
        sf::Sprite getSprite();
        void checkFood(std::vector<Food>& hrana);
        void checkHome(int &pojeli);
        void checkFero(std::vector<Mrav>& mravi);
        std::vector<Marker> &getMarkers();

};