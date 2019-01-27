#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

#define SCREEN_SIZE 800.f
#define GAME_SIZE 200.f

//VARIABLE DEFINITIONS
sf::View view(sf::FloatRect(0, 0, GAME_SIZE, GAME_SIZE));

Player player = Player();
Zombie zombie = Zombie(&player);

std::vector<Bullet> bullets;

sf::RectangleShape r1;
sf::RectangleShape r2;

int main()
{
	//INIT
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Global Game Jam 2019");

	sf::Vector2i anim_priority = sf::Vector2i(0, 0);

	sf::Clock clock;

	player.setPosition(GAME_SIZE / 2, GAME_SIZE / 2);

	//MAIN LOOP
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
					printf("shooting\n");
					Bullet b = Bullet(player.current_dir, player.getPosition());
					bullets.push_back(b);
				}
			}
		}

		sf::Time dt = clock.restart();

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
		player.update(dt);
		zombie.update(dt);

		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].update(dt);
			if (colliding(bullets[i].collider, zombie.collider, bullets[i].getPosition(), zombie.getPosition())) {
				//printf("Colliding\n");
			}
		}

		if (bullets.size() > 0) {
			r1.setSize(sf::Vector2f(bullets[bullets.size() -1].collider.width, bullets[bullets.size() -1].collider.height));
			r1.setPosition(bullets[bullets.size() -1].getPosition());
			r1.setFillColor(sf::Color::Red);
		}
		r2.setSize(sf::Vector2f(zombie.collider.width, zombie.collider.height));

		r2.setPosition(zombie.getPosition());

		//DRAW
		window.setView(view);
		window.clear();

		window.draw(player);
		window.draw(zombie);
		window.draw(r1);
		window.draw(r2);

		for (int i = 0; i < bullets.size(); i++) {
			window.draw(bullets[i]);
		}

		window.display();
	}

	return 0;
}