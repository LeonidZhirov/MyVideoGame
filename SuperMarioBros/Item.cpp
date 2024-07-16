#include "Item.h"
#include "Player.h"


Item::Item(const sf::String& file, const float& x, const float& y, const float& width, const float& height, types_of_items current_type)
	: Object(file, x, y, width, height)
{
	current_type_ = current_type;
	was_eaten_ = false;

	collision_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f);
	sprite_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f);
	collision_.setScale(2.f, 2.f);

	switch (current_type_) {
	case types_of_items::kMushroom:
		sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
		break;
	case types_of_items::kFlower:
		sprite_.setTextureRect(sf::IntRect(32, 0, 16, 16));
		break;
	}
}

Item::types_of_items Item::getCurrentType() const
{
	return current_type_;
}

bool Item::getWasEaten() const
{
	return was_eaten_;
}

void Item::setWasEaten(const bool& was_eaten)
{
	was_eaten_ = was_eaten;
}

