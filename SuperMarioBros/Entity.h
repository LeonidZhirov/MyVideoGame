#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Map.h"

class Entity : public Object
{
public:
	enum class states { kNoState = 0, kStays, kMovingLeft, kMovingRight, kJumps };
	enum class side {kLeft = 0, kRight};

	Entity(const sf::String& file, const float& x, const float& y, const float& width, const float& height);

	bool wasDied() const;
	bool isOnGround() const;

	void setNumberOfLifes(const float& number_of_lifes);

protected:
	int number_of_lifes_;
	bool was_died_, on_ground_;

	states current_state_;
	side current_side_;

	void doEntityAnimations(const float& time, const int& number_of_frames, const float& start_position_x);
};

