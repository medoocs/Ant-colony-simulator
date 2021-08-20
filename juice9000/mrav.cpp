#include "mrav.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include "config.hpp"
#include <deque>
#include "world.h"

Mrav::Mrav(uint32_t idM) {
    id = idM;
    sMrav.setTexture(*Config::tAnt);
    sMrav.setOrigin((*Config::tAnt).getSize().x / 2, (*Config::tAnt).getSize().y / 2);
    sMrav.setScale(0.1f, 0.1f);
    sMrav.setColor(Config::cAnt);
    sMrav.setPosition(Config::width / 2 - (*Config::tAnt).getSize().x / 2 * 0.1f, Config::height / 2 - (*Config::tAnt).getSize().y / 2 * 0.1f);
}

void Mrav::move(sf::Time dt, sf::RenderWindow& window, std::vector<Food>& hrana, std::vector<Mrav>& mravi, bool drawMarkers, std::deque<Marker>& markeri, int& pojeli) {

    float maxSpeed = Config::maxSpeed;
    float steerStrength = Config::steerStrength;
    float wanderStrength = Config::wanderStrength;

    if (flag) {
        position = sMrav.getPosition();
        angles.push_back(sMrav.getRotation());
        flag = false;
    }


    int dir = 1;
    if (!foundFood)
        dir = World::chooseFoodDirection(position, sMrav.getRotation() - 90.f, window);
    else
        dir = World::chooseHomeDirection(position, sMrav.getRotation() - 90.f, window);
    if (dir == 0) {
        float angle2 = (sMrav.getRotation() - 90.f - 20.f) / rad2deg;
        desiredDirection.x = cos(angle2);
        desiredDirection.y = sin(angle2);
    }
    else if (dir == 2) {
        float angle2 = (sMrav.getRotation() - 90.f + 20.f) / rad2deg;
        desiredDirection.x = cos(angle2);
        desiredDirection.y = sin(angle2);
    }

    //odbijanje gore
    if (Utils::delta(position.y, 0.f)) {
        desiredDirection.y = maxSpeed;
    }
    //odbijanje dole
    if (Utils::delta(position.y, (float)Config::height)) {
        desiredDirection.y = -maxSpeed;
    }
    //odbijanje lijevo
    if (Utils::delta(position.x, 0.f)) {
        desiredDirection.x = maxSpeed;
    }
    //odbijanje desno
    if (Utils::delta(position.x, (float)Config::width)) {
        desiredDirection.x = -maxSpeed;
    }

    

    desiredDirection = Utils::normalize(desiredDirection + Utils::randPoint(1.0, 0.0, 0.0) * wanderStrength);
    
    sf::Vector2f desiredVelocity = desiredDirection * maxSpeed;
    sf::Vector2f desiredSteeringForce = (desiredVelocity - velocity) * steerStrength;
    sf::Vector2f acceleration = Utils::ClampMagnitude(desiredSteeringForce, steerStrength);
    velocity = Utils::ClampMagnitude(velocity + acceleration * dt.asSeconds(), maxSpeed);
    position += velocity * dt.asSeconds();
    float angle = (float)atan2(velocity.y, velocity.x) * (float)rad2deg;
    //std::cout << angle <<"\n";
    sMrav.setPosition(position);
    sMrav.setRotation(angle + 90);

    

    checkFood(hrana);
    checkHome(pojeli);

    if (!foundFood)
        World::incHome(sf::Vector2i(position));
    else
        World::incFood(sf::Vector2i(position));
}

sf::Sprite Mrav::getSprite() {
    return sMrav;
}

void Mrav::checkFood(std::vector<Food>& hrana) {
    for (auto& h : hrana) {
        if (Utils::delta(sMrav.getPosition().x, h.getSprite().getPosition().x, 10.f) && Utils::delta(sMrav.getPosition().y, h.getSprite().getPosition().y, 10.f)) {
            if (!foundFood) {
                if (!h.isGone()) {
                    h.eat();
                    foundFood = true;
                    prviFood = true;
                }else {
                    int x = (int)h.getSprite().getPosition().x;
                    int y = (int)h.getSprite().getPosition().y;
                    for (int i = x - 10; i <= x + 10; ++i) {
                        for (int j = y - 10; j <= y - 10; ++j) {
                            World::foodMatrix[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
}

void Mrav::checkHome(int& pojeli) {
    if (Utils::delta(sMrav.getPosition().x, Config::width / 2, 30.f) && Utils::delta(sMrav.getPosition().y, Config::height / 2, 30.f)) {
        if (foundFood) {
            ++pojeli;
            prviHome = true;
        }
            
        foundFood = false;
    }
}

std::vector<Marker>& Mrav::getMarkers() {
    return path;
}