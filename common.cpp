#include "common.h"

sf::Vector2f normalize(sf::Vector2f v)
{
	if (v.x == 0 && v.y == 0)
		return sf::Vector2f(0, 0);

	float mag = sqrt(v.x*v.x + v.y*v.y);
	return sf::Vector2f(v.x / mag, v.y / mag);
}

bool colliding(Collider col1, Collider col2, sf::Vector2f pos1, sf::Vector2f pos2)
{
	col1.left += pos1.x;
	col1.top += pos1.y;

	col2.left += pos2.x;
	col2.top += pos2.y;

	//printf("%f  %f  %f  %f\n", col1.left, col1.top, col1.width, col1.height);

	if (col1.left < col2.left + col2.width &&
		col1.left + col1.width > col2.left &&
		col1.top < col2.top + col2.height &&
		col1.top + col1.height > col2.top) {
		return true;
	}
	return false;

}