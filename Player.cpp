#include "Player.h"

#define I(x, y, w, h) sf::IntRect(x, y, w, h)

#define FRAME_RATE 1.f / 8.f

Player::Player() : AnimatedSprite(sf::seconds(FRAME_RATE))
{
	if (!player_spritesheet.loadFromFile("res/player_spritesheet.png")) {
		printf("Couldn't load player's spritesheet...\n");
	}

	up = Animation();
	up.setSpriteSheet(player_spritesheet);
	up.addFrame(I( 0, 0, 5, 15));
	up.addFrame(I( 5, 0, 5, 15));
	up.addFrame(I(10, 0, 5, 15));
	up.addFrame(I(15, 0, 5, 15));

	down = Animation();
	down.setSpriteSheet(player_spritesheet);
	down.addFrame(I(20, 0, 5, 15));
	down.addFrame(I(25, 0, 5, 15));
	down.addFrame(I(30, 0, 5, 15));
	down.addFrame(I(35, 0, 5, 15));

	right = Animation();
	right.setSpriteSheet(player_spritesheet);
	right.addFrame(I( 0, 15, 9, 15));
	right.addFrame(I(10, 15, 9, 15));
	right.addFrame(I(20, 15, 9, 15));
	right.addFrame(I(30, 15, 9, 15));
	right.addFrame(I(40, 15, 9, 15));
	right.addFrame(I(50, 15, 9, 15));
	right.addFrame(I(60, 15, 9, 15));
	right.addFrame(I(70, 15, 9, 15));

	left = Animation();
	left.setSpriteSheet(player_spritesheet);
	left.addFrame(I( 0, 30, 9, 15));
	left.addFrame(I(10, 30, 9, 15));
	left.addFrame(I(20, 30, 9, 15));
	left.addFrame(I(30, 30, 9, 15));
	left.addFrame(I(40, 30, 9, 15));
	left.addFrame(I(50, 30, 9, 15));
	left.addFrame(I(60, 30, 9, 15));
	left.addFrame(I(70, 30, 9, 15));

	play(left);
}


Player::~Player()
{
}
