#pragma once
#include <SFML/Graphics.hpp>

class Utils {
    public:
        // vraca random point unutar kruznice
        static sf::Vector2f randPoint(float rad, float xc, float yc);
        // normalizacija vektora unity implementacija
        static sf::Vector2f normalize(const sf::Vector2f & source);
        // clampmagnitude implementacija iz unity-a
        static sf::Vector2f ClampMagnitude(sf::Vector2f vector, float maxLength);
        // kvadrat magnitude vektora
        static float sqrMagnitudeFunc(sf::Vector2f vector);
        // epsilon funkcija
        static bool delta(float x, float y, float epsilon = 10.0f);
};