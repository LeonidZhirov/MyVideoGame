#include "Player.h"
#include "View.h"

Player::Player(const sf::String& file, const float& x, const float& y, const float& width, const float& height)
	: Entity(file, x, y, width, height)
{
	sprite_.setOrigin(width_ / 2.f, height_ / 2.f + 8.f);

	sprite_.setTextureRect(sf::IntRect(0, 0, 32, 32));
	player_score_ = 0;
	number_of_lifes_ = 1;
	is_alive_ = true;
	current_power_up_ = power_ups::kNoPowerUp;

	view_ = view;
	view_.reset(sf::FloatRect(0, 0, 640, 480));
}

sf::View Player::getPlayerView() const
{
	return view_;
}

bool Player::getIsFalling() const
{
	return is_falling_;
}

int Player::getNumberOfLifes() const
{
	return number_of_lifes_;
}

void Player::setIsAlive(const bool& is_alive)
{
	is_alive_ = is_alive;
}

void Player::setCollisionAndSprite(const float& width, const float& height)
{
	switch (current_power_up_) {
	case power_ups::kNoPowerUp:
		sprite_.setOrigin(width_ / 2.f, height_ / 2.f + 8.f);
		sprite_.setTextureRect(sf::IntRect(0, 0, width, height));
		break;

	case power_ups::kMushroomPowerUp:
		sprite_.setOrigin(width_ / 2.f, height_ / 2.f);
		collision_.setScale(1.2f, 2.f);
		break;
	}

	x_ = collision_.getGlobalBounds().left;
	y_ = collision_.getGlobalBounds().top;
	width_ = collision_.getGlobalBounds().getSize().x;
	height_ = collision_.getGlobalBounds().getSize().y;
}

void Player::setPowerUp(power_ups power_up)
{
	current_power_up_ = power_up;
}

void Player::control(const float& time)
{
	current_state_ = states::kStays;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		current_side_ = side::kLeft;
		current_state_ = states::kMovingLeft;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		current_side_ = side::kRight;
		current_state_ = states::kMovingRight;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && on_ground_) {
		current_state_ = states::kJumps;
	}
}

void Player::interactionWithItems(Item& item)
{
	if (collision_.getGlobalBounds().intersects(item.getCollisionRect())) {
		switch (item.getCurrentType()) {
		case Item::types_of_items::kMushroom:
			current_power_up_ = power_ups::kMushroomPowerUp;
			setCollisionAndSprite(32.f, 32.f);
			item.setWasEaten(true);
			break;

		case Item::types_of_items::kFlower:
			if (current_power_up_ == power_ups::kMushroomPowerUp) {
				current_power_up_ = power_ups::kFlowerPowerUp;
				setCollisionAndSprite(32.f, 32.f);
				item.setWasEaten(true);
			}
			break;
		}

	}
}

void Player::checkPlayerCollisionWithMap(const float& Dx, const float& Dy)
{
	for (int i = y_ / 32; i < (y_ + height_) / 32; i++)
		for (int j = x_ / 32; j < (x_ + width_) / 32; j++) {
			switch (TileMap[i][j]) {
			case '0':
				if (Dx > 0)
					x_ = j * 32 - width_;
				else if (Dx < 0)
					x_ = j * 32 + 32;

				if (Dy > 0) {
					y_ = i * 32 - height_;
					dy_ = 0;
					on_ground_ = true;
					is_falling_ = false;
				}
				else if (Dy < 0) {
					y_ = i * 32 + 32;
					dy_ = 0;
				}
				break;

			default:
				is_falling_ = true;
				break;
			}
		}
}

void Player::updatePlayer(const float& time)
{
	control(time);

	switch (current_state_)
	{
	case states::kMovingRight:
		dx_ = 0.1f;

		switch (current_power_up_) {
		case power_ups::kNoPowerUp:
			doEntityAnimations(time, 3, 32.f);
			break;
		case power_ups::kMushroomPowerUp:
			doEntityAnimations(time, 3, 288.f);
			break;
		case power_ups::kFlowerPowerUp:
			doEntityAnimations(time, 3, 576.f);
			break;
		}
		break;

	case states::kMovingLeft:
		dx_ = -0.1f;

		switch (current_power_up_) {
		case power_ups::kNoPowerUp:
			doEntityAnimations(time, 3, 32.f);
			break;
		case power_ups::kMushroomPowerUp:
			doEntityAnimations(time, 3, 288.f);
			break;
		case power_ups::kFlowerPowerUp:
			doEntityAnimations(time, 3, 576.f);
			break;
		}
		break;

	case states::kJumps:
		dy_ = -0.7f;
		on_ground_ = false;
		doEntityAnimations(time, 1, 160.f);
		break;

	case states::kStays:
		dx_ = 0.f;
		break;
	}

	x_ += dx_ * time;
	checkPlayerCollisionWithMap(dx_ * 2.f, 0.f);

	y_ += dy_ * time;
	checkPlayerCollisionWithMap(0.f, dy_ * 2.f);

	collision_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f);
	sprite_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f);

	if (!is_alive_)
		number_of_lifes_ -= 1;

	if (number_of_lifes_ <= 0)
		was_died_ = true;

	dy_ = dy_ + 0.0015 * time;

	if (!was_died_)
		setPlayerCoordinateForView(x_, y_, view_);
}
