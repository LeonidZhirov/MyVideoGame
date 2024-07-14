#include "Player.h"
#include "View.h"

Player::Player(const sf::String& file, const float& x, const float& y, const float& width, const float& height)
	: Entity(file, x, y, width, height)
{
	sprite_.setTextureRect(sf::IntRect(0, 0, 32, 32));
	player_score_ = 0; 
	number_of_lifes_ = 3;
	is_alive_ = true;

	view_ = view;
	view_.reset(sf::FloatRect(0, 0, 640, 480));
}

sf::View Player::getPlayerView() const
{
	return view_;
}

void Player::setIsAlive(const bool& is_alive)
{
	is_alive_ = is_alive;
}

void Player::control(const float& time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		current_state_ = states::kLeft;
		speed_ = 0.1f;
		//doAnimations(time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		current_state_ = states::kRight;
		speed_ = 0.1f;
		//doAnimations(time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && on_ground_) {
		current_state_ = states::kJumps;
		dy_ = -0.7f;
		on_ground_ = false;
		//doAnimations(time);
	}
}

void Player::checkCollisionWithMap(const float& Dx, const float& Dy)
{
	for (int i = y_ / 32; i < (y_ + height_) / 32; i++)
		for (int j = x_ / 32; j < (x_ + width_) / 32; j++)
			if (TileMap[i][j] == '0')
			{
				if (Dx > 0)
					x_ = j * 32 - width_;
				else if (Dx < 0)
					x_ = j * 32 + 32;

				if (Dy > 0) {
					y_ = i * 32 - height_;
					dy_ = 0;
					on_ground_ = true;
				}
				else if (Dy < 0) {
					y_ = i * 32 + 32;
					dy_ = 0;
				}
			}
}

void Player::updatePlayer(const float& time)
{
	control(time);

	switch (current_state_)
	{
	case states::kRight:
		dx_ = speed_;
		break;
	case states::kLeft:
		dx_ = -speed_;
		break;

	case states::kJumps:
		break;
	case states::kStays:
		break;
	}

	x_ += dx_ * time;
	checkCollisionWithMap(dx_ * 2.f, 0.f);

	y_ += dy_ * time;
	checkCollisionWithMap(0.f, dy_ * 2.f);

	collision_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f);
	sprite_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f - 16.f);



	//≈сли количество жизней меньше или равно нулю
	if (!is_alive_)
		number_of_lifes_ -= 1;

	if (number_of_lifes_ <= 0)
		was_died_ = false;

	dy_ = dy_ + 0.0015 * time;

	//≈сли персонаж не двигаетс€
	if (!is_moving_)
		speed_ = 0.f;

	//—кроллинг карты при движении игрока
	if (!was_died_)
		setPlayerCoordinateForView(x_, y_, view_);
}