#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Game
{
public:
	Game();

	bool thereIsBlockBelow(sf::RectangleShape blocks[]) const;

	void update();
	void draw();
	void run();
private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Player> player;
	std::unique_ptr<sf::RectangleShape[]> blocks;
};

