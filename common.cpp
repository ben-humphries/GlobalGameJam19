#include "common.h"

sf::Vector2f normalize(sf::Vector2f v)
{
	if (v.x == 0 && v.y == 0)
		return sf::Vector2f(0, 0);

	float mag = sqrt(v.x*v.x + v.y*v.y);
	return sf::Vector2f(v.x / mag, v.y / mag);
}