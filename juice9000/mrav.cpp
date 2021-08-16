#include "mrav.h"
#include "utils.h"
#include <iostream>

Mrav::Mrav() {
    if(!tMrav.loadFromFile("res/ant_2.png"))
        std::cout << "Error nema slike" << std::endl;
    
    tMrav.setSmooth(true);
    sMrav.setTexture(tMrav);
    sMrav.setOrigin(tMrav.getSize().x / 2, tMrav.getSize().y / 2);
    sMrav.setScale(0.2f, 0.2f);
    sMrav.setColor(sf::Color(255, 0, 0));
    sMrav.setPosition(1280 / 2 - tMrav.getSize().x / 2 * 0.2f, 720 / 2 - tMrav.getSize().y / 2 * 0.2f);
}

void Mrav::move(sf::Time dt, sf::RenderWindow& window) {
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
}

sf::Sprite Mrav::getSprite() {
    return sMrav;
}