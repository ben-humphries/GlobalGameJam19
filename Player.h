#pragma once
#include "SFML/Graphics.hpp"
#include "AnimatedSprite.h"
#include "common.h"

class Player : public AnimatedSprite
{
public:
	Player();
	~Player();

	void move(sf::Vector2i move_dir, sf::Vector2i anim_priority, sf::Time dt);

private:
	sf::Texture player_spritesheet;
	Animation up, down, left, right, idle_up, idle_down, idle_left, idle_right;
	Animation current_animation;

	Direction current_dir;
};

