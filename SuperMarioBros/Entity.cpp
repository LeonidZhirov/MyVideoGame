#include "Entity.h"

Entity::Entity(const sf::String& file, const float& x, const float& y, const float& width, const float& height) 
	: Object(file, x , y, width, height)
{
	number_of_lifes_ = 0;

	was_died_ = false; on_ground_ = true;

	current_state_ = states::kNoState;
	current_side_ = side::kRight;
}

bool Entity::wasDied() const
{
	return was_died_;
}

bool Entity::isOnGround() const
{
	return on_ground_;
}

void Entity::setNumberOfLifes(const float& number_of_lifes)
{
	number_of_lifes_ = number_of_lifes;
}


//Защищённые методы
void Entity::doEntityAnimations(const float& time, const int& number_of_frames, const float& start_position_x)
{
	doObjectAnimations(time, number_of_frames);
	
	switch (current_side_) {
	case side::kRight:
		sprite_.setTextureRect(sf::IntRect(start_position_x + (int(current_frame_) * 32), 0, 32, 32));
		break;

	case side::kLeft:
		sprite_.setTextureRect(sf::IntRect(start_position_x + 32 + (int(current_frame_) * 32), 0, -32, 32));
		break;
	}
}
