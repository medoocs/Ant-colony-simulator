#include "world.h"
#include <iostream>
#include "config.h"
#define M_PI  3.141592653f
#define rad2deg (360 / (M_PI * 2))

float World::homeMatrix[Config::width][Config::height] = { 0.f };
float World::foodMatrix[Config::width][Config::height] = { 0.f };
// 3 senzora ispred mrava u obliku kruga, i funkcija prebrojava broj feromona u svakom krugu i tako odlucuje smjer kretanja mrava
int World::chooseDirection(sf::Vector2f& positionMrava, float angleMrav, sf::RenderWindow& window, bool foundFood) {
    // radius senzora
    int s_r = (int)Config::rad_mrav;
    float sensor_count[3] = { 0.f };
    for (int i = -45; i <= 45; i += 45) {

        float angle = angleMrav + i;
        // centar senzora
        int s_x = (int)(positionMrava.x + 35 * cos(angle / rad2deg));
        int s_y = (int)(positionMrava.y + 35 * sin(angle / rad2deg));

        for (int y = (s_y - s_r); y < (s_y + s_r); ++y) {
            for (int x = (s_x - s_r); x < (s_x + s_r); ++x) {
                // provjera da li je u krugu
                if (((x - s_x) * (x - s_x) + (y - s_y) * (y - s_y)) <= s_r * s_r) {
                    if (y < 0 || y >= Config::height || x < 0 || x >= Config::width)
                        continue;
                    if(foundFood)
                        sensor_count[i / 45 + 1] += homeMatrix[(int)x][(int)y];
                    else
                        sensor_count[i / 45 + 1] += foodMatrix[(int)x][(int)y];
                }
            }
        }
    }
    //0 za lijevo, 1 za naprijed i 2 za desno
    int x = (int)(std::max_element(sensor_count, sensor_count + 3) - sensor_count);
    if (sensor_count[x] < Config::follow_force)
        return 1;
    return x;
}

void World::incHome(sf::Vector2i pos) {
    if (pos.y < 0 || pos.y >= Config::height || pos.x < 0 || pos.x >= Config::width)
        return;
    
    homeMatrix[pos.x][pos.y] += Config::hInc;
    if (homeMatrix[pos.x][pos.y] >= 1) homeMatrix[pos.x][pos.y] = 1;
}
void World::incFood(sf::Vector2i pos) {
    if (pos.y < 0 || pos.y >= Config::height || pos.x < 0 || pos.x >= Config::width)
        return;
    
    foodMatrix[pos.x][pos.y] += Config::fInc;
    if (foodMatrix[pos.x][pos.y] >= 1) foodMatrix[pos.x][pos.y] = 1;
}
void World::decHome(sf::Vector2i pos) {
    if (pos.y < 0 || pos.y >= Config::height || pos.x < 0 || pos.x >= Config::width)
        return;
    homeMatrix[pos.x][pos.y] -= Config::hDec;
}
void World::decFood(sf::Vector2i pos) {
    if (pos.y < 0 || pos.y >= Config::height || pos.x < 0 || pos.x >= Config::width)
        return;
    foodMatrix[pos.x][pos.y] -= Config::fDec;
}