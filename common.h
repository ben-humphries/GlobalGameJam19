#pragma once
#include "SFML/Graphics.hpp"

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#define I(x, y, w, h) sf::IntRect(x, y, w, h)
#define Collider sf::FloatRect

#define FRAME_RATE 1.f / 8.f

sf::Vector2f normalize(sf::Vector2f v);

bool colliding(Collider col1, Collider col2, sf::Vector2f pos1, sf::Vector2f pos2);

float random_float(float a, float b);
