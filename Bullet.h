#pragma once
#include "common.h"

class Bullet : public sf::Transformable, public sf::Drawable
{
public:
	Bullet(Direction dir, sf::Vector2f position);
	~Bullet();

	void update(sf::Time dt);

	Collider collider;

private:
	Direction dir;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	sf::Texture texture;
	sf::Sprite sprite;

};

