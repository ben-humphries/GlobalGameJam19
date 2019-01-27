#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"

#define I(x, y, w, h) sf::IntRect(x, y, w, h)

//VARIABLE DEFINITIONS
Player player = Player();

int main()
{
	//ASSIGN PLAYER ANIMATIONS
	sf::Texture player_spritesheet;

	{
		if (!player_spritesheet.loadFromFile("res/player_spritesheet.png")) {
			printf("Couldn't load player's spritesheet...\n");
			return 1;
		}

		Animation * up = new Animation();
		up->setSpriteSheet(player_spritesheet);
		up->addFrame(I( 0, 0, 5, 16));
		up->addFrame(I( 5, 0, 5, 16));
		up->addFrame(I(10, 0, 5, 16));
		up->addFrame(I(15, 0, 5, 16));

		player.play(*up);
	}
	sf::RenderWindow window(sf::VideoMode(200, 200), "Global Game Jam 2019");


	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time dt = clock.restart();
		
		//UPDATE
		player.update(dt);

		//DRAW
		window.clear();
		window.draw(player);
		window.display();
	}

	return 0;
}