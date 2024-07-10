#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Object
{
public:
	Object(const sf::Vector2f& position, const sf::Vector2f& collisionSize, const sf::Vector2f& collisionScale, const sf::Vector2f& spriteScale, 
		const std::string& textureName, const int& x, const int& y, const int& width, const int& height);

	//Getters
	sf::FloatRect getCollisionGlobalBounds() const;

	//Setters
	void setPosition(const float& x, const float& y);

	void draw(sf::RenderWindow* window);

protected:
	sf::RectangleShape collision;
	std::unique_ptr<sf::Texture> texture;
	sf::Sprite sprite;
};

