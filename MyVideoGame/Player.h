#pragma once
#include "Entity.h"

class Player : 
	public Entity
{
public:
	Player(const sf::Vector2f& position, const sf::Vector2f& collisionSize, const sf::Vector2f& collisionScale, const sf::Vector2f& spriteScale,
		const std::string& textureName, const int& x, const int& y, const int& width, const int& height)
		: Entity(position, collisionSize, collisionScale, spriteScale, textureName, x, y, width, height) {};

};

