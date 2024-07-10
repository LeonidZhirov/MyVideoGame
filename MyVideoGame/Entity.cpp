#include "Entity.h"

bool Entity::getOnGround() const
{
	return on_ground_;
}

Entity::type_of_action Entity::getCurrentAction() const
{
	return currentAction;
}

void Entity::setVelocityX(const float& velocity_x_)
{
	this->velocity_x_ = velocity_x_;
}

void Entity::setVelocityY(const float& velocity_y_)
{
	this->velocity_y_ = velocity_y_;
}

void Entity::setOnGround(const bool& on_ground_)
{
	this->on_ground_ = on_ground_;
}

void Entity::setCurrentAction(type_of_action action)
{
	currentAction = action;
}

bool Entity::isAlive(const float& lower_bound) const
{
	if (collision.getGlobalBounds().getPosition().y >= lower_bound)
		return true;
	return false;
}

void Entity::isFalling(const float& obstacle, const bool& thereIsBlockBelow)
{
	if (!thereIsBlockBelow || collision.getGlobalBounds().top + collision.getGlobalBounds().height <= obstacle) {
		velocity_y_ += gravity_;
		collision.move(velocity_x_, velocity_y_);
		sprite.move(velocity_x_, velocity_y_);
	}
	else if (thereIsBlockBelow && collision.getGlobalBounds().top + collision.getGlobalBounds().height > obstacle) {
		velocity_y_ = 0.f;
		collision.setPosition(collision.getGlobalBounds().getPosition().x, obstacle - collision.getGlobalBounds().height);
		sprite.setPosition(sprite.getGlobalBounds().getPosition().x, obstacle - sprite.getGlobalBounds().height);
		on_ground_ = true;
		updateMovementX();
	}
}

/*bool Entity::checkCollisions(std::shared_ptr<Entity> entity) const
{
	std::shared_ptr<Entity> temp_player = entity;

	if

		return false;
}*/

void Entity::changeSide(type_of_action action)
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

void Entity::control()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		currentAction = type_of_action::MOVING_LEFT;
		//speed = 0.1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		currentAction = type_of_action::MOVING_RIGHT;
		//speed = 0.1;

	}
}

void Entity::updateMovementX()
{
	collision.move(velocity_x_, 0);
	sprite.move(velocity_x_, 0);
}