#pragma once
#include "SFML/Graphics.hpp"

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#define I(x, y, w, h) sf::IntRect(x, y, w, h)

#define FRAME_RATE 1.f / 8.f

sf::Vector2f normalize(sf::Vector2f v);