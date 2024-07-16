#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

class Game
{
public:
	Game();

	void update();
	void draw();

	void gameRunning();

private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Player> player;

	std::unique_ptr<Enemy> koopa;
	std::list<std::unique_ptr<Enemy>> goombas;
	std::list<std::unique_ptr<Enemy>>::iterator it;
	std::list<std::unique_ptr<Enemy>>::iterator it2;

	std::list<std::unique_ptr<Item>> items;
	std::list<std::unique_ptr<Item>>::iterator it3;

	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_map;

	sf::Clock clock;
};