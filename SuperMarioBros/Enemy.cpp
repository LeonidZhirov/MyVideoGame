#include "Enemy.h"
#include "Map.h"

Enemy::Enemy(const sf::String& file, const float& x, const float& y, const float& width, const float& height, types_of_enemies type)
	: Entity(file, x, y, width, height)
{
	is_deleted_ = false;
	type_ = type;
	number_of_lifes_ = 1;

	switch (type_) {
	case types_of_enemies::goomba:
		sprite_.setTextureRect(sf::IntRect(0, 0, width, height));
		dx_ = 0.1f;
		break;
	case types_of_enemies::koopa:
		break;
	}
}

Enemy::types_of_enemies Enemy::getType() const
{
	return type_;
}

bool Enemy::getIsDeleted() const
{
	return is_deleted_;
}

void Enemy::setIsDeleted(const bool& is_deleted)
{
	is_deleted_ = is_deleted;
}

void Enemy::checkCollisionWithMap(const float& Dx, const float& Dy)
{
	for (int i = y_ / 32; i < (y_ + height_) / 32; i++)
		for (int j = x_ / 32; j < (x_ + width_) / 32; j++)
			if (TileMap[i][j] == '0')
			{
				if (Dx > 0) {
					x_ = j * 32 - width_;
					current_state_ = states::kLeft;
					dx_ *= -1.f;
				}
				else if (Dx < 0) {
					x_ = j * 32 + 32;
					current_state_ = states::kRight;
					dx_ *= -1.f;
				}

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

void Enemy::update(const float& time)
{
	switch (type_) {
	case types_of_enemies::goomba:
		checkCollisionWithMap(dx_ * 2.f, 0.f);
		x_ += dx_ * time;

		collision_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f);
		sprite_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f - 16.f);

		//Если здоровье меньше нуля
		if (number_of_lifes_ <= 0)
			was_died_ = true;

		break;
	}
}
