#include "mrav.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include "config.hpp"

Mrav::Mrav(uint32_t idM) {
    id = idM;
    sMrav.setTexture(*Config::tAnt);
    sMrav.setOrigin((*Config::tAnt).getSize().x / 2, (*Config::tAnt).getSize().y / 2);
    sMrav.setScale(0.2f, 0.2f);
    sMrav.setColor(Config::cAnt);
    sMrav.setPosition(1280 / 2 - (*Config::tAnt).getSize().x / 2 * 0.2f, 720 / 2 - (*Config::tAnt).getSize().y / 2 * 0.2f);
}

void Mrav::move(sf::Time dt, sf::RenderWindow& window, std::vector<Food>& hrana, std::vector<Mrav>& mravi, bool drawMarkers) {
    
    if (wander) {
        float maxSpeed = 500;
        float steerStrength = 200;
        float wanderStrength = 1;

        if (flag) {
            position = sMrav.getPosition();
            flag = false;
        }

        //odbijanje gore
        if (Utils::delta(position.y, 0.f)) {
            desiredDirection.y = 0.5;
        }
        //odbijanje dole
        if (Utils::delta(position.y, 720.f)) {
            desiredDirection.y = -0.5;
        }
        //odbijanje lijevo
        if (Utils::delta(position.x, 0.f)) {
            desiredDirection.x = 0.5;
        }
        //odbijanje desno
        if (Utils::delta(position.x, 1280.f)) {
            desiredDirection.x = -0.5;
        }

        desiredDirection = Utils::normalize(desiredDirection + Utils::randPoint(1.0, 0.0, 0.0) * wanderStrength);
        sf::Vector2f desiredVelocity = desiredDirection * maxSpeed;
        sf::Vector2f desiredSteeringForce = (desiredVelocity - velocity) * steerStrength;
        sf::Vector2f acceleration = Utils::ClampMagnitude(desiredSteeringForce, steerStrength);
        velocity = Utils::ClampMagnitude(velocity + acceleration * dt.asSeconds(), maxSpeed);
        position += velocity * dt.asSeconds();
        float angle = (float)atan2(velocity.y, velocity.x) * (float)rad2deg;

        sMrav.setPosition(position);
        sMrav.setRotation(angle + 90);
        steps++;
        
        fullPositions.push_back(position);
        angles.push_back(angle + 90);
        path.emplace_back(position);
        for (auto p : path) {
            p.changeToDefault();
            p.setBlack(false);
            //std::cout << "usan u wander\n";
            if (drawMarkers) window.draw(p.getSprite());
        }
        
        checkFood(hrana);
        checkFero(mravi);
    }
    else if (!wander && toHome) {
        for (auto p : path) {
            p.changeColor();
            p.setBlack(true);
            if (drawMarkers) window.draw(p.getSprite());
        }
        checkFood(hrana);
        if (steps == 0) {
            toHome = false;
            toFood = true;
        }
        else {
            sMrav.setPosition(fullPositions[steps - 1]);
            sMrav.setRotation(angles[steps - 1] + 180);
            steps--;
        }
        
    }
    else if (!wander && toFood) {
        for (auto p : path) {
            p.changeColor();
            p.setBlack(true);
            if (drawMarkers) window.draw(p.getSprite());
        }
        checkFood(hrana);
        if (steps == (fullPositions.size() )) {
            if (foodAlive) {
                toFood = false;
                toHome = true;
                foodAlive = true;
                wander = false;
            }
            else {
                toFood = false; 
                toHome = false; 
                foodAlive = false; 
                wander = true;
            }
        }
        else {
            sMrav.setPosition(fullPositions[steps]);
            sMrav.setRotation(angles[steps]);
            steps++;
        }
        
    }
}

sf::Sprite Mrav::getSprite() {
    return sMrav;
}

void Mrav::checkFood(std::vector<Food>& hrana) {
    for (auto &h : hrana) {
        if (sMrav.getGlobalBounds().intersects(h.getSprite().getGlobalBounds())){
            if (!toHome) {
                h.eat();

                wander = false;
                toFood = false;
                toHome = true;
                if (h.getAmount() == 0) foodAlive = false;
                else foodAlive = true;
            }
        }
    }
}

std::vector<Marker>& Mrav::getMarkers() {
    return path;
}

void Mrav::checkFero(std::vector<Mrav>& mravi) {
    for (auto& m : mravi) {
        std::vector<Marker> tmp = m.getMarkers();
        //if(tmp.size()) std::cout << tmp[0].getBlack() << "\n";
        if ((m.id != id) && tmp.size() && (m.toFood || m.toHome)) {
            uint32_t ct = 0;
            for (auto& f : tmp) {
                ct++;
                if (sMrav.getGlobalBounds().intersects(f.getSprite().getGlobalBounds())) {
                    if (wander) {
                        fullPositions.insert(fullPositions.end(), m.fullPositions.begin() + ct, m.fullPositions.end());
                        angles.insert(angles.end(), m.angles.begin() + ct, m.angles.end());
                        toHome = false;
                        toFood = true;
                        foodAlive = true;
                        wander = false;
                    }
                }
            }
        }      
    }
}

