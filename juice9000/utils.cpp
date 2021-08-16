#include "utils.h"

bool Utils::delta(float x, float y, float epsilon) {
    if (fabs(x - y) < epsilon)
        return true;
    return false;
}

float Utils::sqrMagnitudeFunc(sf::Vector2f vector) {
    return vector.x * vector.x + vector.y * vector.y;
}

sf::Vector2f Utils::ClampMagnitude(sf::Vector2f vector, float maxLength)
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

sf::Vector2f Utils::normalize(const sf::Vector2f& source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

sf::Vector2f Utils::randPoint(float rad, float xc, float yc) {
    float ang, hyp, adj, opp;
    ang = (float)rand() / RAND_MAX * 2 * M_PI;
    hyp = sqrt((float)rand() / RAND_MAX) * rad;
    adj = cos(ang) * hyp;
    opp = sin(ang) * hyp;
    sf::Vector2f v(xc + adj, yc + opp);
    return v;
}