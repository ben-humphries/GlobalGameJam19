#include "Zombie.h"

Zombie::Zombie(Player * target) : AnimatedSprite(sf::seconds(FRAME_RATE))
{

	this->target = target;

	if (!zombie_spritesheet.loadFromFile("res/zombie_spritesheet.png")) {
		printf("Couldn't load zombie's spritesheet...\n");
	}

	up = Animation();
	up.setSpriteSheet(zombie_spritesheet);
	up.addFrame(I(0, 0, 5, 15));
	up.addFrame(I(5, 0, 5, 15));
	up.addFrame(I(10, 0, 5, 15));
	up.addFrame(I(15, 0, 5, 15));

	down = Animation();
	down.setSpriteSheet(zombie_spritesheet);
	down.addFrame(I(20, 0, 5, 15));
	down.addFrame(I(25, 0, 5, 15));
	down.addFrame(I(30, 0, 5, 15));
	down.addFrame(I(35, 0, 5, 15));

	left = Animation();
	left.setSpriteSheet(zombie_spritesheet);
	left.addFrame(I(0, 15, 9, 15));
	left.addFrame(I(9, 15, 9, 15));
	left.addFrame(I(18, 15, 9, 15));
	left.addFrame(I(27, 15, 9, 15));
	left.addFrame(I(36, 15, 9, 15));
	left.addFrame(I(45, 15, 9, 15));
	left.addFrame(I(54, 15, 9, 15));
	left.addFrame(I(63, 15, 9, 15));

	right = Animation();
	right.setSpriteSheet(zombie_spritesheet);
	right.addFrame(I(0, 31, 9, 15));
	right.addFrame(I(9, 31, 9, 15));
	right.addFrame(I(18, 31, 9, 15));
	right.addFrame(I(27, 31, 9, 15));
	right.addFrame(I(36, 31, 9, 15));
	right.addFrame(I(45, 31, 9, 15));
	right.addFrame(I(54, 31, 9, 15));
	right.addFrame(I(63, 31, 9, 15));


	current_animation = left; //idle
	current_dir = DOWN;
	play(current_animation);
}

void Zombie::update(sf::Time dt)
{
	AnimatedSprite::update(dt);

	float speed = 20;

	sf::Vector2f player_dir = normalize(target->getPosition() - this->getPosition());
	move(player_dir * speed * dt.asSeconds());

	if (player_dir.x > 0.5) { current_animation = right; current_dir = RIGHT; }
	else if (player_dir.x < -0.5) { current_animation = left; current_dir = LEFT; }
	else if (player_dir.y > 0) { current_animation = down; current_dir = DOWN; }
	else if (player_dir.y < 0) { current_animation = up; current_dir = UP; }

}


Zombie::~Zombie()
{
}
