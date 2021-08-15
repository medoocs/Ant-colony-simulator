#include "mrav.h"
#include <iostream>
Mrav::Mrav() {
    std::cout << "Konstruktor" << std::endl;
    if(!tMrav.loadFromFile("res/ant_2.png"))
        std::cout << "Error nema slike" << std::endl;
    
    tMrav.setSmooth(true);
    sMrav.setTexture(tMrav);
    sMrav.setOrigin(tMrav.getSize().x / 2, tMrav.getSize().y / 2);
    sMrav.setScale(0.2f, 0.2f);
    sMrav.setColor(sf::Color(255, 0, 0));
    sMrav.setPosition(1280 / 2 - tMrav.getSize().x / 2 * 0.2f, 720 / 2 - tMrav.getSize().y / 2 * 0.2f);

    std::cout << "222" << std::endl;
}

void Mrav::move(sf::Time dt, sf::RenderWindow& window) {
    std::cout << "Move" << std::endl;
    float maxSpeed = 500;
    float steerStrength = 200;
    float wanderStrength = 1;

    if (flag) {
        position = sMrav.getPosition();
        flag = false;
    }
    
    //odbijanje gore
    if (delta(position.y, 0.f)) {
        desiredDirection.y = 0.5;
    }
    //odbijanje dole
    if (delta(position.y, 720.f)) {
        desiredDirection.y = -0.5;
    }
    //odbijanje lijevo
    if (delta(position.x, 0.f)) {
        desiredDirection.x = 0.5;
    }
    //odbijanje desno
    if (delta(position.x, 1280.f)) {
        desiredDirection.x = -0.5;
    }
    desiredDirection = normalize(desiredDirection + randPoint(1.0, 0.0, 0.0) * wanderStrength);

    sf::Vector2f desiredVelocity = desiredDirection * maxSpeed;
    sf::Vector2f desiredSteeringForce = (desiredVelocity - velocity) * steerStrength;
    sf::Vector2f acceleration = ClampMagnitude(desiredSteeringForce, steerStrength);

    velocity = ClampMagnitude(velocity + acceleration * dt.asSeconds(), maxSpeed);
    position += velocity * dt.asSeconds();




    float angle = (float)atan2(velocity.y, velocity.x) * (float)rad2deg;
    sMrav.setPosition(position);
    sMrav.setRotation(angle + 90);
}

bool Mrav::delta(float x, float y, float epsilon) {
    if (fabs(x - y) < epsilon)
        return true;
    return false;
}

float Mrav::sqrMagnitudeFunc(sf::Vector2f vector) {
    return vector.x * vector.x + vector.y * vector.y;
}

sf::Vector2f Mrav::ClampMagnitude(sf::Vector2f vector, float maxLength)
{
    float sqrMagnitude = sqrMagnitudeFunc(vector);
    if (sqrMagnitude > maxLength * maxLength)
    {
        float mag = (float)sqrt(sqrMagnitude);

        float normalized_x = vector.x / mag;
        float normalized_y = vector.y / mag;
        return sf::Vector2f(normalized_x * maxLength,
            normalized_y * maxLength);
    }
    return vector;
}

sf::Vector2f Mrav::normalize(const sf::Vector2f& source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

sf::Vector2f Mrav::randPoint(float rad, float xc, float yc) {
    float ang, hyp, adj, opp;
    ang = (float)rand() / RAND_MAX * 2 * M_PI;
    hyp = sqrt((float)rand() / RAND_MAX) * rad;
    adj = cos(ang) * hyp;
    opp = sin(ang) * hyp;
    sf::Vector2f v(xc + adj, yc + opp);
    return v;
}
