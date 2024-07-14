#include "Entity.h"

Entity::Entity(const sf::String& file, const float& x, const float& y, const float& width, const float& height)
{
	x_ = x; y_ = y;
	width_ = width; height_ = height;
	dx_ = 0.f; dy_ = 0.f; speed_ = 0.f;
	number_of_lifes_ = 0;

	was_died_ = false; is_moving_ = false; on_ground_ = false;

	current_frame_ = 0.f;
	current_state_ = states::kStays;

	collision_.setSize(sf::Vector2f(width_, height_));
	collision_.setOrigin(width_ / 2.f, height_ / 2.f);
	collision_.setFillColor(sf::Color::Green);

	texture_.loadFromFile("images/" + file);

	sprite_.setTexture(texture_);
	sprite_.setOrigin(width_ / 2.f, height_ / 2.f);
	sprite_.setScale(2.f, 2.f);
}

float Entity::getDx() const
{
	return dx_;
}

float Entity::getDy() const
{
	return dy_;
}

sf::FloatRect Entity::getRect() const
{
	return sf::FloatRect(x_, y_, width_, height_);
}

bool Entity::wasDied() const
{
	return was_died_;
}


bool Entity::isOnGround() const
{
	return on_ground_;
}

void Entity::setDx(const float& dx)
{
	dx_ = dx;
}

void Entity::setDy(const float& dy)
{
	dy_ = dy;
}

void Entity::setNumberOfLifes(const float& number_of_lifes)
{
	number_of_lifes_ = number_of_lifes;
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(collision_);
	window.draw(sprite_);
}

//Защищённые методы
void Entity::doAnimations(const float& time)
{
	current_frame_ += 0.005 * time;

	if (current_frame_ > 3)
		current_frame_ -= 3;

	sprite_.setTextureRect(sf::IntRect(96 * int(current_frame_), 135, 96, 54));
}
