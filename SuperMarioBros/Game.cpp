#include "Game.h"
#include "Map.h"

Game::Game()
{
	//Создаёи окно и игрока
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 480), "Lesson 20. kychka-pc.ru");
	player = std::make_unique<Player>("Mario.png", 250.f, 500.f, 32.f, 32.f);

	for (int i = 0; i < 3; i++)
		goombas.push_back(std::make_unique<Enemy>("Enemies.png", 850.f + i * 45.f, 736.f, 32.f, 32.f, Enemy::types_of_enemies::goomba));

	map_image.loadFromFile("images/OverWorld.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);
	s_map.setScale(2.f, 2.f);
}

void Game::update()
{
	float time = clock.getElapsedTime().asMicroseconds();

	clock.restart();
	time = time / 800;

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}

	//Обновляем игрока
	player->updatePlayer(time);

	for (it = goombas.begin(); it != goombas.end(); ) {
		it->get()->update(time);

		if (it->get()->wasDied()) {
			(*it)->setIsDeleted(true);
			it = goombas.erase(it);
		}
		else
			it++;
	}

	for (it = goombas.begin(); it != goombas.end(); it++)
	{
		if ((*it)->getRect().intersects(player->getRect()))
		{
			switch ((*it)->getType()) {
			case Enemy::types_of_enemies::goomba:
				if (player->getDy() > 0 && !player->isOnGround()) {
					(*it)->setDx(0.f);
					player->setDy(-0.2f);
					(*it)->setNumberOfLifes(0);
				}
				else
					player->setIsAlive(false);
			}
		}
	}

	window->setView(player->getPlayerView());
}

void Game::draw()
{
	window->clear();

	//Отрисовываем игровую карту
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			switch (TileMap[i][j]) {
			case ' ':
				s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
				break;
			case 's':
				s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
				break;
			case '0':
				s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
				break;
			case 'f':
				s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
				break;
			case 'h':
				s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));
				break;
			}
			s_map.setPosition(j * 32, i * 32);

			window->draw(s_map);
		}

	//Отрисовываем персонажа
	player->draw(*(window.get()));

	for (it = goombas.begin(); it != goombas.end(); it++)
		if (!(*it)->getIsDeleted())
			it->get()->draw(*(window.get()));

	window->display();
}

void Game::isWorking()
{
	while (window->isOpen()) {
		update();
		draw();
	}
}