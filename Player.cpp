#include "Player.h"

#define FRAME_RATE 1.f / 8.f

Player::Player() : AnimatedSprite(sf::seconds(FRAME_RATE))
{
}


Player::~Player()
{
}
