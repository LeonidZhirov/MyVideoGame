#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	Game();

	void update();
	void draw();

	void isWorking();

private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Player> player;
	std::list<std::unique_ptr<Enemy>> goombas;
	std::list<std::unique_ptr<Enemy>>::iterator it;

	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_map;

	sf::Clock clock;
};