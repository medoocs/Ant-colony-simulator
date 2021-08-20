#include "world.h"
#include <iostream>
#include "config.hpp"
#define M_PI  3.141592653
#define rad2deg (360 / (M_PI * 2))

float World::homeMatrix[1280][720] = { 0.f };
float World::foodMatrix[1280][720] = { 0.f };

int World::chooseHomeDirection(sf::Vector2f& positionMrava, float angleMrav, sf::RenderWindow& window) {
    float s_r = Config::rad_mrav;
    float sensor_count[3] = { 0.f };
    for (int i = -45; i <= 45; i += 45) {

        float angle = angleMrav + i;

        int s_x = positionMrava.x + 35 * cos(angle / rad2deg);
        int s_y = positionMrava.y + 35 * sin(angle / rad2deg);

        for (int y = s_y - s_r; y < s_y + s_r; ++y) {
            for (int x = s_x - s_r; x < s_x + s_r; ++x) {
                if (((x - s_x) * (x - s_x) + (y - s_y) * (y - s_y)) <= s_r * s_r) {
                    if (y < 0 || y >= 720 || x < 0 || x >= 1280)
                        continue;

                    sensor_count[i / 45 + 1] += homeMatrix[(int)x][(int)y];
                }
            }
        }
    }
    int x = std::max_element(sensor_count, sensor_count + 3) - sensor_count;
    if (sensor_count[x] < 10/*1e-6*/)
        return 1;
    return x;
}

int World::chooseFoodDirection(sf::Vector2f& positionMrava, float angleMrav, sf::RenderWindow& window) {
    float s_r = Config::rad_mrav;
    float sensor_count[3] = { 0.f };
    for (int i = -45; i <= 45; i += 45) {
        float angle = angleMrav + i;

        int s_x = positionMrava.x + 35 * cos(angle / rad2deg);
        int s_y = positionMrava.y + 35 * sin(angle / rad2deg);


        for (int y = s_y - s_r; y < s_y + s_r; ++y) {
            for (int x = s_x - s_r; x < s_x + s_r; ++x) {
                if (((x - s_x) * (x - s_x) + (y - s_y) * (y - s_y)) <= s_r * s_r) {
                    if (y < 0 || y >= 720 || x < 0 || x >= 1280)
                        continue;
                    sensor_count[i / 45 + 1] += foodMatrix[(int)x][(int)y];
                }
            }
        }
    }
    int x = std::max_element(sensor_count, sensor_count + 3) - sensor_count;
    if (sensor_count[x] < 10/*1e-6*/)
        return 1;
    return x;
}

void World::incHome(sf::Vector2i pos) {
    if (pos.y < 0 || pos.y >= 720 || pos.x < 0 || pos.x >= 1280)
        return;
    
    homeMatrix[pos.x][pos.y] += 0.5f;
    if (homeMatrix[pos.x][pos.y] >= 1) homeMatrix[pos.x][pos.y] = 1;
}
void World::incFood(sf::Vector2i pos) {
    if (pos.y < 0 || pos.y >= 720 || pos.x < 0 || pos.x >= 1280)
        return;
    
    foodMatrix[pos.x][pos.y] += 0.5f;
    if (foodMatrix[pos.x][pos.y] >= 1) foodMatrix[pos.x][pos.y] = 1;
}
void World::decHome(sf::Vector2i pos) {
    if (pos.y < 0 || pos.y >= 720 || pos.x < 0 || pos.x >= 1280)
        return;
    homeMatrix[pos.x][pos.y] -= 0.005f;
}
void World::decFood(sf::Vector2i pos) {
    if (pos.y < 0 || pos.y >= 720 || pos.x < 0 || pos.x >= 1280)
        return;
    foodMatrix[pos.x][pos.y] -= 0.005f;
}