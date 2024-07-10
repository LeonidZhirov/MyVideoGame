#include "Object.h"

Object::Object(const sf::Vector2f& position, const sf::Vector2f& collisionSize, const sf::Vector2f& collisionScale, const sf::Vector2f& spriteScale,
	const std::string& textureName, const int& x, const int& y, const int& width, const int& height)
{
	collision.setSize(collisionSize);
	collision.setScale(collisionScale);
	collision.setOrigin(width / 2.f, height / 2.f);
	collision.setPosition(position.x + width / 2.f, position.y + height / 2.f);

	texture = std::make_unique<sf::Texture>();
	texture->loadFromFile(textureName);
	sprite.setTexture(*(texture.get()));

	sprite.setTextureRect(sf::IntRect(x, y, width, height));
	sprite.setScale(spriteScale);
	sprite.setOrigin(width / 2.f, height / 2.f);
	sprite.setPosition(position.x  + width / 2.f, position.y  + height / 2.f);
}

sf::FloatRect Object::getCollisionGlobalBounds() const
{
	return collision.getGlobalBounds();
}

void Object::setPosition(const float& x, const float& y)
{
	collision.setPosition(x, y);
	sprite.setPosition(x, y);
}

void Object::draw(sf::RenderWindow* window)
{
	window->draw(collision);
	window->draw(sprite);
}
