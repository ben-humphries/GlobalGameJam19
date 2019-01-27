#include "Bullet.h"



Bullet::Bullet(Direction dir, sf::Vector2f position)
{
	this->dir = dir;

	if (!texture.loadFromFile("res/bullet.png")) {
		printf("Couldn't load bullet image...\n");
	}

	if (dir == UP || dir == DOWN)
		position.x += 2;
	if (dir == DOWN)
		position.y += 13;

	if (dir == LEFT || dir == RIGHT)
		position.y += 5;
	if (dir == RIGHT)
		position.x += 7;

	setPosition(position);

	sprite.setTexture(texture);

	collider = Collider(0, 0, 4, 4);

	sprite.setColor(sf::Color(247, 222, 13));
}


Bullet::~Bullet()
{
}

void Bullet::update(sf::Time dt)
{
	float speed = 200;
	
	sf::Vector2f v_dir;
	
	switch (dir) {
	case UP:
		v_dir = sf::Vector2f(0, -1);
		break;
	case DOWN:
		v_dir = sf::Vector2f(0, 1);
		break;
	case LEFT:
		v_dir = sf::Vector2f(-1, 0);
		break;
	case RIGHT:
		v_dir = sf::Vector2f(1, 0);
		break;
	}

	move(v_dir * speed * dt.asSeconds());
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
		states.transform *= getTransform();
		states.texture = &texture;
		target.draw(sprite, states);
}
