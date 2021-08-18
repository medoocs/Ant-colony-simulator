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
    sMrav.setPosition(1280 / 2 - (*Config::tAnt).getSize().x / 2 * 0.1f, 720 / 2 - (*Config::tAnt).getSize().y / 2 * 0.1f);
}

void Mrav::move(sf::Time dt, sf::RenderWindow& window, std::vector<Food>& hrana, std::vector<Mrav>& mravi, bool drawMarkers, std::deque<Marker> &markeri, int &pojeli) {
    
    float maxSpeed = 200;
    float steerStrength = 50;
    float wanderStrength = 0.5;

    if (flag) {
        position = sMrav.getPosition();
        angles.push_back(sMrav.getRotation());
        flag = false;
    }

    
    int dir = 1;
    if(!foundFood)
        dir = World::chooseFoodDirection(position, sMrav.getRotation() - 90.f, window);
    else
        dir = World::chooseHomeDirection(position, sMrav.getRotation() - 90.f, window);
    if (dir == 0) {
        float angle2 = (sMrav.getRotation() -90.f - 15.f)/rad2deg;
        desiredDirection.x = cos(angle2);
        desiredDirection.y = sin(angle2);
    }
    else if (dir == 2) {
        float angle2 = (sMrav.getRotation() -90.f + 15.f) / rad2deg;
        desiredDirection.x = cos(angle2);
        desiredDirection.y = sin(angle2);
    }

    //odbijanje gore
    if (Utils::delta(position.y, 0.f)) {
        desiredDirection.y = maxSpeed;
    }
    //odbijanje dole
    if (Utils::delta(position.y, 720.f)) {
        desiredDirection.y = -maxSpeed;
    }
    //odbijanje lijevo
    if (Utils::delta(position.x, 0.f)) {
        desiredDirection.x = maxSpeed;
    }
    //odbijanje desno
    if (Utils::delta(position.x, 1280.f)) {
        desiredDirection.x = -maxSpeed;
    }

    //desiredDirection = Utils::normalize(desiredDirection + Utils::randPoint(1.0, 0.0, 0.0) * wanderStrength);

    sf::Vector2f desiredVelocity = desiredDirection * maxSpeed;
    sf::Vector2f desiredSteeringForce = (desiredVelocity - velocity) * steerStrength;
    sf::Vector2f acceleration = Utils::ClampMagnitude(desiredSteeringForce, steerStrength);
    velocity = Utils::ClampMagnitude(velocity + acceleration * dt.asSeconds(), maxSpeed);
    position += velocity * dt.asSeconds();
    float angle = (float)atan2(velocity.y, velocity.x) * (float)rad2deg;
    //std::cout << angle <<"\n";
    sMrav.setPosition(position);
    sMrav.setRotation(angle + 90);

    if (steps % 1000 == 0) {
        markeri.emplace_back(position);
        if (markeri.size() > 5) markeri.pop_front();
    }

    checkFood(hrana);
    checkHome(pojeli);

    if(!foundFood)
        World::incHome(sf::Vector2i(position));
    else
        World::incFood(sf::Vector2i(position));
}

sf::Sprite Mrav::getSprite() {
    return sMrav;
}

void Mrav::checkFood(std::vector<Food>& hrana) {
    for (auto& h : hrana) {
        if ( Utils::delta(sMrav.getPosition().x, h.getSprite().getPosition().x, 10.f) && Utils::delta(sMrav.getPosition().y, h.getSprite().getPosition().y, 10.f) ) {
            if (!foundFood) {
                h.eat();
                foundFood = true;
            }
        }
    }
}

void Mrav::checkHome(int &pojeli) {
    if (Utils::delta(sMrav.getPosition().x, 1280/2, 15.f) && Utils::delta(sMrav.getPosition().y, 720/2, 15.f)) {
        if (foundFood)
            ++pojeli;
        foundFood = false;
    }
}

std::vector<Marker>& Mrav::getMarkers() {
    return path;
}

