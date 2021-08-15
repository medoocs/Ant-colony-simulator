#pragma once
#include <SFML/Graphics.hpp>

#define M_PI  3.141592653
#define rad2deg (360 / (M_PI * 2))

class Mrav{
    private:
        sf::Texture tMrav;
        sf::Vector2f position, velocity, desiredDirection;
        bool flag = true;

	public:
        sf::Sprite sMrav;
        Mrav();
        ~Mrav() = default;
        void move(sf::Time dt, sf::RenderWindow& window);
        sf::Vector2f randPoint(float rad, float xc, float yc);
        sf::Vector2f normalize(const sf::Vector2f& source);
        sf::Vector2f ClampMagnitude(sf::Vector2f vector, float maxLength);
        float sqrMagnitudeFunc(sf::Vector2f vector);
        bool delta(float x, float y, float epsilon = 100.0f);
};