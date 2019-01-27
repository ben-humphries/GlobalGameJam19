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

sf::Font font;
sf::Text score_text;

sf::Texture home_texture;
sf::Sprite home_sprite;

int score = 0;

bool isDead = false;

void reset();

bool isMenu = true;
bool isShowingScore = false;

float zombie_time = 10.f;
float elapsed_time = 0.0f;
float spawn_rate = 0.0f;

int selected = PLAY;

int main()
{
	//INIT
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Global Game Jam 2019");

	sf::Vector2i anim_priority = sf::Vector2i(0, 0);

	sf::Clock clock;

	player.setPosition(GAME_SIZE / 2 - 3, GAME_SIZE / 2 - 7);

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

	font.loadFromFile("res/BEBAS.ttf");
	score_text = sf::Text("Score: ", font);
	score_text.setCharacterSize(10);
	score_text.setPosition(0, 0);

	if (!home_texture.loadFromFile("res/home.png")) {
		printf("Couldn't load home texture...\n");
	}
	home_sprite.setTexture(home_texture);
	home_sprite.setOrigin(5, 5);
	home_sprite.setPosition(GAME_SIZE / 2, GAME_SIZE / 2);

	sf::Text play_text = sf::Text("PLAY", font);
	play_text.setPosition(GAME_SIZE / 2, GAME_SIZE / 2 + 20);
	play_text.setCharacterSize(20);
	play_text.setOrigin(play_text.getGlobalBounds().width / 2, play_text.getGlobalBounds().height / 2);

	sf::Text quit_text = sf::Text("QUIT", font);
	quit_text.setPosition(GAME_SIZE / 2, GAME_SIZE / 2 + 60);
	quit_text.setCharacterSize(20);
	quit_text.setOrigin(quit_text.getGlobalBounds().width / 2, quit_text.getGlobalBounds().height / 2);

	sf::Text title_text = sf::Text("HOME  MEANS\nFIGHTING  OFF\nTHE  ZOMBIE\nAPOCALYPSE", font);
	title_text.setPosition(GAME_SIZE / 2, GAME_SIZE / 2 + - 40);
	title_text.setCharacterSize(15);
	title_text.setOrigin(title_text.getGlobalBounds().width / 2, title_text.getGlobalBounds().height / 2);
	title_text.setFillColor(sf::Color::Black);


	//MAIN LOOP
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {

				if (!isMenu && !isShowingScore) {
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

					else if (event.key.code == sf::Keyboard::Escape) {
						isMenu = true;
					}
				}
				else if (isMenu){
					if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
						selected--;
						if (selected < 0) selected = 1;
					}
					else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
						selected++;
						if (selected > 1) selected = 0;
					}
					else if (event.key.code == sf::Keyboard::Enter) {
						if (selected == PLAY) {
							reset();
							isMenu = false;
						}
						else if (selected == QUIT) {
							window.close();
						}
					}
					else if (event.key.code == sf::Keyboard::Escape) {
						window.close();
					}
				}

				else if (isShowingScore) {
					if (event.key.code == sf::Keyboard::Escape) {
						isMenu = true;
						reset();
					}

					else if (event.key.code == sf::Keyboard::Enter) {
						reset();
					}
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (!isMenu) {
					if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up ||
						event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left ||
						event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down ||
						event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
						anim_priority = sf::Vector2i(0, 0);
					}
				}
			}
		}

		if (isMenu) {

			if (selected == PLAY) {
				play_text.setFillColor(sf::Color::White);
				play_text.setCharacterSize(25);
				play_text.setOrigin(play_text.getGlobalBounds().width / 2, play_text.getGlobalBounds().height / 2);
			}
			else {
				play_text.setFillColor(sf::Color::Black);
				play_text.setCharacterSize(20);
				play_text.setOrigin(play_text.getGlobalBounds().width / 2, play_text.getGlobalBounds().height / 2);
			}

			if (selected == QUIT) {
				quit_text.setFillColor(sf::Color::White);
				quit_text.setCharacterSize(25);
				quit_text.setOrigin(quit_text.getGlobalBounds().width / 2, quit_text.getGlobalBounds().height / 2);
			}
			else {
				quit_text.setFillColor(sf::Color::Black);
				quit_text.setCharacterSize(20);
				quit_text.setOrigin(quit_text.getGlobalBounds().width / 2, quit_text.getGlobalBounds().height / 2);
			}

			window.setView(view);
			window.clear(sf::Color(107, 74, 38));
			window.draw(title_text);
			background_sprite.setColor(sf::Color(255, 255, 255));
			window.draw(background_sprite);
			window.draw(play_text);
			window.draw(quit_text);
			window.display();
			continue;
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

		if (!isShowingScore) {
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
		}

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
					score++;
				}
				++z_it;
			}
			++it;
		}

		//DRAW
		lightmap_texture.clear(sf::Color(100, 100, 100));
		score_text.setString("Score: " + std::to_string(score));
		window.setView(view);
		window.clear(sf::Color(107,74,38));

		window.draw(home_sprite);

		if (!isShowingScore) {
			window.draw(player);
		}

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

		if (isShowingScore) {
			score_text.setPosition(GAME_SIZE / 2 - score_text.getGlobalBounds().width / 2, GAME_SIZE / 2 - score_text.getGlobalBounds().height / 2 - 30);
		}
		window.draw(score_text);
		window.display();

		if (isDead)
			isShowingScore = true;
	}

	return 0;
}

void reset()
{
	bullets.clear();
	zombies.clear();
	score = 0;
	player.setPosition(GAME_SIZE / 2 - 3, GAME_SIZE / 2 - 7);
	isDead = false;
	elapsed_time = 0;
	zombie_time = 0;
	spawn_rate = 0.0;
	selected = PLAY;
	score_text.setPosition(0, 0);
	isShowingScore = false;
}