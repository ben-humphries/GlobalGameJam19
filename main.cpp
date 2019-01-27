#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Zombie.h"

#define SCREEN_SIZE 800.f
#define GAME_SIZE 128.f

//VARIABLE DEFINITIONS
sf::View view(sf::FloatRect(0, 0, GAME_SIZE, GAME_SIZE));

Player player = Player();
Zombie zombie = Zombie(&player);

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Global Game Jam 2019");

	sf::Vector2i anim_priority = sf::Vector2i(0, 0);

	sf::Clock clock;
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

		//DRAW
		window.setView(view);
		window.clear();
		window.draw(player);
		window.draw(zombie);
		window.display();
	}

	return 0;
}