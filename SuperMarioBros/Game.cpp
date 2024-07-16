#include "Game.h"

Game::Game()
{
	//Создаёи окно, игрока и купу
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 480), "Lesson 20. kychka-pc.ru");
	player = std::make_unique<Player>("Mario.png", 100.f, 400.f, 32.f, 32.f);
	koopa = std::make_unique<Enemy>("Enemies.png", 930.f, 736.f, 32.f, 32.f, Enemy::types_of_enemies::koopa, Enemy::koopa_states::turtle);

	//Создаём предметы
	for (int i = 0; i < 2; i++)
		if (i == 0)
			items.push_back(std::make_unique<Item>("Items.png", 200.f, 450.f, 16.f, 16.f, Item::types_of_items::kMushroom));
		else
			items.push_back(std::make_unique<Item>("Items.png", 350.f, 450.f, 16.f, 16.f, Item::types_of_items::kFlower));

	//Создаём гумбу
	for (int i = 0; i < 1; i++)
		goombas.push_back(std::make_unique<Enemy>("Enemies.png", 850.f + i * 33.f, 736.f, 32.f, 32.f, Enemy::types_of_enemies::goomba, Enemy::koopa_states::not_koopa));

	//Передаём текстуру карты и создаём спрайт элемента карты
	map_image.loadFromFile("Images/OverWorld.png");
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

	//Обновляем купу и рассматриваем его взаимодейтсвие с игроком
	koopa->update(time);
	koopa->interactionWithPlayer(*player);

	//Обновляем гумб и удаляем их из списка, если они мертвы
	for (it = goombas.begin(); it != goombas.end(); ) {
		(*it)->update(time);

		if ((*it)->wasDied()) 
			it = goombas.erase(it);
		else
			it++;
	}

	for (it3 = items.begin(); it3 != items.end(); ) {
		player->interactionWithItems(*(it3->get()));

		if ((*it3)->getWasEaten())
			it3 = items.erase(it3);
		else
			it3++;
	}

	for (it = goombas.begin(); it != goombas.end(); it++) {
		(*it)->interactionWithPlayer(*player);
		
		for (it2 = goombas.begin(); it2 != goombas.end(); it2++) {
			if ((*it)->getCollisionRect() == (*it2)->getCollisionRect())
				continue;

			(*it)->interactionWithOtherEnemies(*(it2->get()));
		}

		(*it)->interactionWithOtherEnemies(*koopa);
	}

	window->setView(player->getPlayerView());
}

void Game::draw()
{
	window->clear(sf::Color(146, 144, 255));

	//Отрисовываем игровую карту
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			switch (TileMap[i][j]) {
			case '0':
				s_map.setTextureRect(sf::IntRect(0, 0, 16, 16));
				s_map.setColor(sf::Color::White);
				break;

			case ' ':
				s_map.setColor(sf::Color::Transparent);
				break;
			}
			s_map.setPosition(j * 32, i * 32);

			window->draw(s_map);
		}

	//Отрисовываем персонажа
	player->draw(*(window));
	koopa->draw(*(window));

	for (it = goombas.begin(); it != goombas.end(); it++)
		if (!(*it)->getIsDeleted())
			(*it)->draw(*(window));

	for (it3 = items.begin(); it3 != items.end(); it3++)
		if (!(*it3)->getWasEaten())
			(*it3)->draw(*(window));

	window->display();
}

void Game::gameRunning()
{
	while (window->isOpen()) {
		if (!player->wasDied()) {
			update();
			draw();
		}
		else
			window->close();
	}
}

