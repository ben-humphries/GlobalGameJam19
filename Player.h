#pragma once
#include "SFML/Graphics.hpp"
#include "AnimatedSprite.h"

class Player : public AnimatedSprite
{
public:
	Player();
	~Player();

private:
	sf::Texture player_spritesheet;
	Animation up, down, left, right;
};

