#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <Windows.h>
#define M_PI  3.141592653
#define rad2deg (360 / (M_PI * 2))
sf::Vector2f position, velocity, desiredDirection, oneandone(1.0f, 1.0f);
bool flag = true;
int ct = 0;

bool delta(float x, float y, float epsilon =100.0f) {
    if (fabs(x - y) < epsilon)
        return true; 
    return false; 
}
float sqrMagnitudeFunc(sf::Vector2f vector) {
    return vector.x * vector.x + vector.y * vector.y;
}

sf::Vector2f ClampMagnitude(sf::Vector2f vector, float maxLength)
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

sf::Vector2f normalize(const sf::Vector2f& source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

sf::Vector2f randPoint(float rad, float xc, float yc) {
    float ang, hyp, adj, opp;
    ang = (float)rand() / RAND_MAX * 2 * M_PI;
    hyp = sqrt((float)rand() / RAND_MAX) * rad;
    adj = cos(ang) * hyp;
    opp = sin(ang) * hyp;
    sf::Vector2f v(xc + adj, yc + opp);
    return v;
}

void draw(std::vector<sf::Sprite>& shapes, sf::RenderWindow& window) {
    for (auto s : shapes) {
        window.draw(s);
    }
}

void move(std::vector<sf::Sprite>& shapes, sf::Time dt, sf::RenderWindow& window) {

    float maxSpeed = 500;
    float steerStrength = 200;
    float wanderStrength = 1;
    if (flag) {
        position = shapes[0].getPosition();
        flag = false;
    }
    for (auto& s : shapes) {
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
        s.setPosition(position);
        s.setRotation(angle + 90);
        std::cout << position.x << "  " << position.y << "  " << angle << std::endl;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mravi9000");
    window.setFramerateLimit(144);
    std::vector<sf::Sprite> shapes;

    //mravinjak
    sf::Texture tMravinjak;
    if (!tMravinjak.loadFromFile("res/marker.png"))
        return -1;
    tMravinjak.setSmooth(true);
    sf::Sprite sMravinjak;
    sMravinjak.setTexture(tMravinjak);
    sMravinjak.setScale(1.5f, 1.5f);
    sMravinjak.setColor(sf::Color(165, 42, 42));
    sMravinjak.setPosition(1280 / 2 - tMravinjak.getSize().x / 2 * 1.5f, 720 / 2 - tMravinjak.getSize().y / 2 * 1.5f);

    //mrav
    sf::Texture tMrav;
    if (!tMrav.loadFromFile("res/ant_2.png"))
        return -1;
    tMrav.setSmooth(true);
    sf::Sprite sMrav;
    sMrav.setTexture(tMrav);
    sMrav.setOrigin(tMrav.getSize().x / 2, tMrav.getSize().y / 2);
    sMrav.setScale(0.2f, 0.2f);
    sMrav.setColor(sf::Color(255, 0, 0));
    sMrav.setPosition(1280 / 2 - tMrav.getSize().x / 2 * 0.2f, 720 / 2 - tMrav.getSize().y / 2 * 0.2f);
    std::cout << 1280 / 2 - tMrav.getSize().x / 2 * 0.2f << "  " << 720 / 2 - tMrav.getSize().y / 2 * 0.2f << std::endl;
    shapes.push_back(sMrav);

    sf::Vector2f v;
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //clear
        window.clear(sf::Color(49, 99, 0));
        window.draw(sMravinjak);
        //moving
        move(shapes, dt, window);
        draw(shapes, window);
        v = randPoint(1.0, 0.0, 0.0);
        //std::cout << v.x << " " << v.y << std::endl;
        //display
        window.display();
    }

    return 0;
}