#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

#include <list>

#define SCREEN_SIZE 800.f
#define GAME_SIZE 200.f

//VARIABLE DEFINITIONS
sf::View view(sf::FloatRect(0, 0, GAME_SIZE, GAME_SIZE));

Player player = Player();

std::list<Bullet> bullets;
std::list<Zombie> zombies;

int main()
{
	//INIT
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Global Game Jam 2019");

	sf::Vector2i anim_priority = sf::Vector2i(0, 0);

	sf::Clock clock;

	player.setPosition(GAME_SIZE / 2, GAME_SIZE / 2);

	//MAIN LOOP
	float elapsedTime = 10.f;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::W) {
					anim_priority = sf::Vector2i(0, -1);
				}
				else if (event.key.code == sf::Keyboard::A) {
					anim_priority = sf::Vector2i(-1, 0);
				}
				else if (event.key.code == sf::Keyboard::S) {
					anim_priority = sf::Vector2i(0, 1);
				}
				else if (event.key.code == sf::Keyboard::D) {
					anim_priority = sf::Vector2i(1, 0);
				}

				else if (event.key.code == sf::Keyboard::Space) {
					Bullet b = Bullet(player.current_dir, player.getPosition());
					bullets.push_back(b);
				}
			}
		}

		sf::Time dt = clock.restart();
		elapsedTime += dt.asSeconds();

		//INPUT
		sf::Vector2i to_move = sf::Vector2i(0, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			to_move.y -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			to_move.x -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			to_move.y += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			to_move.x += 1;
		}

		player.move(to_move, anim_priority, dt);


		//UPDATE

		if (elapsedTime >= 0.3f) {
			Zombie * zombie = new Zombie(&player);
			sf::Vector2f position;

			if (random_float(0, 1) > 0.5) {
				position.x = random_float(0, GAME_SIZE);
				position.y = 0;
			}
			else {
				position.x = 0;
				position.y = random_float(0, GAME_SIZE);
			}

			zombie->setPosition(position);
			zombies.push_back(*zombie);
			elapsedTime = 0;
		}

		player.update(dt);

		std::list<Zombie>::iterator z_it = zombies.begin();
		while (z_it != zombies.end())
		{
			(*z_it).update(dt);
			z_it++;
		}

		std::list<Bullet>::iterator it = bullets.begin();
		while (it != bullets.end())
		{

			sf::Vector2f bulletPos = (*it).getPosition();

			if (bulletPos.x > GAME_SIZE + 10 || bulletPos.x < -10 || bulletPos.y > GAME_SIZE + 10 || bulletPos.y < -10) {
				bullets.erase(it++);
			}
			(*it).update(dt);

			z_it = zombies.begin();
			while (z_it != zombies.end())
			{
				if (colliding((*it).collider, (*z_it).collider, (*it).getPosition(), (*z_it).getPosition())) {
					zombies.erase(z_it++);
				}
				++z_it;
			}
			++it;
		}

		//DRAW
		window.setView(view);
		window.clear();

		window.draw(player);

		z_it = zombies.begin();
		while (z_it != zombies.end())
		{
			window.draw(*z_it);
			z_it++;
		}

		it = bullets.begin();
		while (it != bullets.end())
		{
			window.draw(*it);
			it++;
		}

		window.display();
	}

	return 0;
}