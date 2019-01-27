#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

#include <list>


//VARIABLE DEFINITIONS
sf::View view(sf::FloatRect(0, 0, GAME_SIZE, GAME_SIZE));

Player player = Player();

std::list<Bullet> bullets;
std::list<Zombie> zombies;

sf::Texture background_texture;
sf::Sprite  background_sprite;

sf::Texture light_texture;
sf::Sprite light_sprite;

sf::RenderTexture lightmap_texture;
sf::Sprite lightmap_sprite;


bool isDead = false;

void reset();

int main()
{
	//INIT
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Global Game Jam 2019");

	sf::Vector2i anim_priority = sf::Vector2i(0, 0);

	sf::Clock clock;

	player.setPosition(GAME_SIZE / 2, GAME_SIZE / 2);

	if (!background_texture.loadFromFile("res/background_f.png")) {
		printf("Couldn't load background texture\n");
	}

	background_sprite.setTexture(background_texture);

	lightmap_texture.create(GAME_SIZE, GAME_SIZE);
	lightmap_sprite.setTexture(lightmap_texture.getTexture());

	if (!light_texture.loadFromFile("res/light.png")) {
		printf("Couldn't load light texture\n");
	}
	light_sprite.setTexture(light_texture);
	light_sprite.setOrigin(25, 25);

	//MAIN LOOP
	float zombie_time = 10.f;
	float elapsed_time = 0.0f;
	float spawn_rate = 0.0f;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
					anim_priority = sf::Vector2i(0, -1);
				}
				else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
					anim_priority = sf::Vector2i(-1, 0);
				}
				else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
					anim_priority = sf::Vector2i(0, 1);
				}
				else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
					anim_priority = sf::Vector2i(1, 0);
				}

				else if (event.key.code == sf::Keyboard::Space) {
					Bullet b = Bullet(player.current_dir, player.getPosition());
					bullets.push_back(b);
				}
			}
		}
		sf::Time dt = clock.restart();
		zombie_time += dt.asSeconds();
		elapsed_time += dt.asSeconds();

		if (elapsed_time < 10.0) {
			spawn_rate = 0.5f;
		}
		else if (elapsed_time < 30.0) {
			spawn_rate = 1.0f;
		}
		else if (elapsed_time < 60.0) {
			spawn_rate = 2.0f;
		}

		//INPUT
		sf::Vector2i to_move = sf::Vector2i(0, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			to_move.y -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			to_move.x -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			to_move.y += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			to_move.x += 1;
		}

		player.move(to_move, anim_priority, dt);


		//UPDATE

		if (zombie_time >= 1 / spawn_rate) {
			Zombie * zombie = new Zombie(&player);
			sf::Vector2f position;

			if (random_float(0, 1) > 0.5) {
				position.x = random_float(0, GAME_SIZE);
				if (random_float(0, 1) > 0.5)
					position.y = 0;
				else
					position.y = GAME_SIZE;
			}
			else {
				if (random_float(0, 1) > 0.5)
					position.x = 0;
				else
					position.x = GAME_SIZE;
				position.y = random_float(0, GAME_SIZE);
			}

			zombie->setPosition(position);
			zombies.push_back(*zombie);
			zombie_time = 0;
		}

		player.update(dt);

		std::list<Zombie>::iterator z_it = zombies.begin();
		while (z_it != zombies.end())
		{
			(*z_it).update(dt);
			if (colliding((*z_it).collider, player.collider, (*z_it).getPosition(), player.getPosition())) {
				isDead = true;
			}
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
		lightmap_texture.clear(sf::Color(100, 100, 100));
		window.setView(view);
		window.clear(sf::Color(107,74,38));

		window.draw(player);
		light_sprite.setPosition(player.getPosition().x + 3, GAME_SIZE - player.getPosition().y - 7);
		light_sprite.setScale(2.0, 2.0);
		lightmap_texture.draw(light_sprite, sf::BlendAdd);

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
			light_sprite.setPosition((*it).getPosition().x, GAME_SIZE - (*it).getPosition().y);
			light_sprite.setScale(0.25, 0.25);
			lightmap_texture.draw(light_sprite, sf::BlendAdd);
			it++;
		}

		window.draw(lightmap_sprite, sf::BlendMultiply);
		//window.draw(light_sprite);

		background_sprite.setColor(sf::Color(100, 100, 100));
		window.draw(background_sprite);


		window.display();

		if (isDead)
			reset();
	}

	return 0;
}

void reset()
{
	bullets.clear();
	zombies.clear();
	player.setPosition(GAME_SIZE / 2, GAME_SIZE / 2);
	isDead = false;
}