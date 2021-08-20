#include "mrav.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include "config.h"
#include "world.h"
#define M_PI  3.141592653f
#define rad2deg (360 / (M_PI * 2))

Mrav::Mrav(uint32_t idM) {
    id = idM;
    sMrav.setTexture(*Config::tAnt);
    sMrav.setOrigin((*Config::tAnt).getSize().x / 2.f, (*Config::tAnt).getSize().y / 2.f);
    sMrav.setScale(0.1f, 0.1f);
    sMrav.setColor(Config::cAnt);
    sMrav.setPosition(Config::width / 2 - (*Config::tAnt).getSize().x / 2 * 0.1f, Config::height / 2 - (*Config::tAnt).getSize().y / 2 * 0.1f);
}

void Mrav::move(sf::Time dt, sf::RenderWindow& window, std::vector<Food>& hrana, std::vector<Mrav>& mravi, int& pojeli) {

    float maxSpeed = Config::maxSpeed;
    float steerStrength = Config::steerStrength;
    float wanderStrength = Config::wanderStrength;
    // za prvi frame
    if (flag) {
        position = sMrav.getPosition();
        flag = false;
    }

    // biranje smjera kretnje ovisno o feromonima
    int dir = 1;
    if (!foundFood)
        dir = World::chooseDirection(position, sMrav.getRotation() - 90.f, window, foundFood);
    else
        dir = World::chooseDirection(position, sMrav.getRotation() - 90.f, window, foundFood);
    // kretanje Config::deg_mrav u lijevo/desno
    if (dir == 0) {
        float angle2 = (sMrav.getRotation() - 90.f - Config::deg_mrav) / rad2deg;
        desiredDirection.x = cos(angle2);
        desiredDirection.y = sin(angle2);
    }
    else if (dir == 2) {
        float angle2 = (sMrav.getRotation() - 90.f + Config::deg_mrav) / rad2deg;
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
    // racunanje positiona i angle mrava
    // nakon odredivanja desired directiona zbraja se randdom tocka iz kruznice kako bi postojao nekakav RNG 
    // u kretnji mrava uz nekakvu varijablu koja odreduje jacinu odluke da mrav skrene
    desiredDirection = Utils::normalize(desiredDirection + Utils::randPoint(1.0, 0.0, 0.0) * wanderStrength);
    
    sf::Vector2f desiredVelocity = desiredDirection * maxSpeed;
    sf::Vector2f desiredSteeringForce = (desiredVelocity - velocity) * steerStrength;
    sf::Vector2f acceleration = Utils::ClampMagnitude(desiredSteeringForce, steerStrength);
    velocity = Utils::ClampMagnitude(velocity + acceleration * dt.asSeconds(), maxSpeed);
    position += velocity * dt.asSeconds();
    float angle = (float)atan2(velocity.y, velocity.x) * (float)rad2deg;
    sMrav.setPosition(position);
    sMrav.setRotation(angle + 90);
    // provjera kolizija
    checkFood(hrana);
    checkHome(pojeli);
    // increment feromona
    if (!foundFood)
        World::incHome(sf::Vector2i(position));
    else
        World::incFood(sf::Vector2i(position));
}
// vraca sprite mrava
sf::Sprite Mrav::getSprite() {
    return sMrav;
}
// provjerava koliziju mrava i hrane za svaki frame
void Mrav::checkFood(std::vector<Food>& hrana) {
    for (auto& h : hrana) {
        if (((sMrav.getPosition().x - h.getSprite().getPosition().x) * (sMrav.getPosition().x - h.getSprite().getPosition().x) + (sMrav.getPosition().y - h.getSprite().getPosition().y) * (sMrav.getPosition().y - h.getSprite().getPosition().y)) <= Config::rad_food * Config::rad_food){
            if (!foundFood) {
                if (!h.isGone()) {
                    // desila se kolizija, jedi hranu
                    h.eat();
                    foundFood = true;
                }else {
                    // ciscenje feromona sa mjesta gdje se nalazila hrana
                    sf::CircleShape tmp = h.getSprite();
                    int x = (int)tmp.getPosition().x;
                    int y = (int)tmp.getPosition().y;
                    for (int i = x - (int)Config::rad_food; i <= x + (int)Config::rad_food; ++i) {
                        for (int j = y - (int)Config::rad_food; j <= y - (int)Config::rad_food; ++j) {
                            World::foodMatrix[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
}
// kolizija mrava i mravinjaka
void Mrav::checkHome(int& pojeli) {
    if (((sMrav.getPosition().x - Config::width / 2) * (sMrav.getPosition().x - Config::width / 2) + (sMrav.getPosition().y - Config::height / 2) * (sMrav.getPosition().y - Config::height / 2)) <= Config::rad_mravinjak * Config::rad_mravinjak){
        if (foundFood) {
            // desila se kolizija deposit hranu
            ++pojeli;
        }
            
        foundFood = false;
    }
}
