#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "common.h"

class Zombie : public AnimatedSprite
{
public:
	Zombie(Player * target);
	~Zombie();

	void update(sf::Time dt);

	Collider collider;

private:
	sf::Texture zombie_spritesheet;
	Animation up, down, left, right;
	Animation * current_animation;

	Direction current_dir;

	Player * target;
};

