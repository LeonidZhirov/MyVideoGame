#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class Player;

class Item : public Object
{
public:
	enum class types_of_items { kCoin = 0, kMushroom, kFlower, kLife };

	Item(const sf::String& file, const float& x, const float& y, const float& width, const float& height, types_of_items current_type);

	types_of_items getCurrentType() const;
	bool getWasEaten() const;

	void setWasEaten(const bool& was_eaten);

private:
	types_of_items current_type_;
	bool was_eaten_;
};

