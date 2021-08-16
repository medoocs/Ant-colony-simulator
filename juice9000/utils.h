#pragma once
#include <SFML/Graphics.hpp>
#define M_PI  3.141592653

class Utils {
    public:
        static sf::Vector2f randPoint(float rad, float xc, float yc);
        static sf::Vector2f normalize(const sf::Vector2f & source);
        static sf::Vector2f ClampMagnitude(sf::Vector2f vector, float maxLength);
        static float sqrMagnitudeFunc(sf::Vector2f vector);
        static bool delta(float x, float y, float epsilon = 100.0f);
};