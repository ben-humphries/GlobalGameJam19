#include "Player.h"


Player::Player() : AnimatedSprite(sf::seconds(FRAME_RATE))
{
	if (!player_spritesheet.loadFromFile("res/player_spritesheet.png")) {
		printf("Couldn't load player's spritesheet...\n");
	}

	collider = Collider(1, 3, 2, 5);

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

	idle_up = Animation();
	idle_up.setSpriteSheet(player_spritesheet);
	idle_up.addFrame(I(5, 0, 5, 15));

	idle_down = Animation();
	idle_down.setSpriteSheet(player_spritesheet);
	idle_down.addFrame(I(25, 0, 5, 15));

	idle_left = Animation();
	idle_left.setSpriteSheet(player_spritesheet);
	idle_left.addFrame(I(60, 0, 9, 15));

	idle_right = Animation();
	idle_right.setSpriteSheet(player_spritesheet);
	idle_right.addFrame(I(70, 0, 9, 15));

	current_animation = idle_down; //idle
	current_dir = DOWN;
	play(current_animation);
}


Player::~Player()
{
}

void Player::move(sf::Vector2i move_dir, sf::Vector2i anim_priority, sf::Time dt)
{
	float speed = 50;
	AnimatedSprite::move((sf::Vector2f) move_dir * speed * dt.asSeconds());

	if (move_dir.y > 0) { current_animation = down; current_dir = DOWN; }
	else if (move_dir.y < 0) { current_animation = up; current_dir = UP; }
	if (move_dir.x > 0) { current_animation = right; current_dir = RIGHT; }
	else if (move_dir.x < 0) { current_animation = left; current_dir = LEFT; }

	if (anim_priority.x == -1) { current_animation = left; current_dir = LEFT; }
	if (anim_priority.x == 1) { current_animation = right; current_dir = RIGHT; }
	if (anim_priority.y == -1) { current_animation = up; current_dir = UP; }
	if (anim_priority.y == 1) { current_animation = down; current_dir = DOWN; }



	if (move_dir.x == 0 && move_dir.y == 0) {
		switch (current_dir) {
		case UP:
			current_animation = idle_up;
			break;
		case DOWN:
			current_animation = idle_down;
			break;
		case LEFT:
			current_animation = idle_left;
			break;
		case RIGHT:
			current_animation = idle_right;
			break;
		default:
			printf("Something went wrong in player animation\n");
		}
	}

	if (getPosition().x > GAME_SIZE) setPosition(GAME_SIZE, getPosition().y);
	else if (getPosition().x < 0) setPosition(0, getPosition().y);
	if (getPosition().y > GAME_SIZE) setPosition(getPosition().x, GAME_SIZE);
	else if (getPosition().y < 0) setPosition(getPosition().x, 0);

}