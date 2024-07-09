#include "Player.h"

Player::Player()
{
	texture.loadFromFile("Images/Mario.png"); // Длина каждого спрайта 32*32

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setScale(2.f, 2.f);
	sprite.setPosition(200.f, 320.f - (sprite.getGlobalBounds().getSize().y + 20.f));

	collision.setSize(sf::Vector2f(32.f, 32.f));
	collision.setScale(1.1f, 1.1f);
	collision.setPosition(215.f, 320.f - (collision.getGlobalBounds().getSize().y + 20.f));

}

bool Player::getOnGround() const
{
	return on_ground_;
}

sf::RectangleShape Player::getCollision() const
{
	return collision;
}

sf::Sprite Player::getSprite() const
{
	return sprite;
}

Player::type_of_action Player::getCurrentAction() const
{
	return currentAction;
}

void Player::setVelocityX(const float& velocity_x_)
{
	this->velocity_x_ = velocity_x_;
}

void Player::setVelocityY(const float& velocity_y_)
{
	this->velocity_y_ = velocity_y_;
}

void Player::setOnGround(const bool& on_ground_)
{
	this->on_ground_ = on_ground_;
}

void Player::setCurrentAction(type_of_action action)
{
	currentAction = action;
}

void Player::setPosition(const float& x, const float& y)
{
	collision.setPosition(x, y);
	sprite.setPosition(x - 14.f, y - 29.f);
}

bool Player::isAlive(const float& lower_bound) const
{
	if (collision.getGlobalBounds().getPosition().y >= lower_bound)
		return true;
	return false;
}

void Player::isFalling(const float& obstacle, const bool& thereIsBlockBelow)
{
	if (!thereIsBlockBelow || collision.getGlobalBounds().top + collision.getGlobalBounds().height <= obstacle) {
		velocity_y_ += gravity_;
		collision.move(velocity_x_, velocity_y_);
		sprite.move(velocity_x_, velocity_y_);
	}
	else if (thereIsBlockBelow && collision.getGlobalBounds().top + collision.getGlobalBounds().height > obstacle) {
		collision.setPosition(collision.getGlobalBounds().getPosition().x , obstacle - collision.getGlobalBounds().height);
		sprite.setPosition(sprite.getGlobalBounds().getPosition().x, obstacle - sprite.getGlobalBounds().height);
		on_ground_ = true;
		updateMovementX();
	}
}

void Player::changeSide(type_of_action action)
{
	switch (action) {
	case type_of_action::MOVING_LEFT:
		sprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
		break;
	case type_of_action::MOVING_RIGHT:
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	}
}

void Player::updateMovementX()
{
	collision.move(velocity_x_, 0);
	sprite.move(velocity_x_, 0);
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(collision);
	window->draw(sprite);
}
