#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(const sf::String& file, const float& x, const float& y, const float& width, const float& height, types_of_enemies type, koopa_states koopa_state)
	: Entity(file, x, y, width, height)
{
	is_deleted_ = false;
	type_ = type;
	koopa_state_ = koopa_state;
	number_of_lifes_ = 1;
	interactions_with_player_ = 0;

	switch (type_) {
	case types_of_enemies::goomba:
		sprite_.setTextureRect(sf::IntRect(0, 0, width, height));
		dx_ = 0.1f;
		break;
	case types_of_enemies::koopa:
		sprite_.setTextureRect(sf::IntRect(96, 0, width, height));
		dx_ = 0.1f;
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

Enemy::koopa_states Enemy::getKoopaState() const
{
	return koopa_state_;
}

void Enemy::interactionWithPlayer(Player& player)
{
	if (collision_.getGlobalBounds().intersects(player.getCollisionRect())) {
		switch (type_) {
		case types_of_enemies::goomba:
			if ((player.getDy() > 0 && !player.isOnGround()) || player.getIsFalling()) {
				dx_ = 0.f;
				player.setDy(-0.2f);
				number_of_lifes_ = 0;
			}
			else
				player.setIsAlive(false);

			break;

		case types_of_enemies::koopa:
			switch (interactions_with_player_) {
			case 0:
				if ((player.getDy() > 0 && !player.isOnGround()) || player.getIsFalling()) {
					dx_ = 0.f;
					player.setDy(-0.2f);
					interactions_with_player_++;
					koopa_state_ = koopa_states::turtle;
				}
				else
					player.setIsAlive(false);

				break;
			case 1:
				dx_ = player.getDx() * 3.f;
				interactions_with_player_ = 0;
				koopa_state_ = koopa_states::shell;

				break;
			}

			break;
		}
	}
}

void Enemy::interactionWithOtherEnemies(Enemy& enemy)
{
	if (getCollisionRect().intersects(enemy.getCollisionRect())) {
		if (koopa_state_ != koopa_states::shell && enemy.getKoopaState() != koopa_states::shell) {
			dx_ *= -1.f;
			enemy.setDx(enemy.getDx() * -1.f);
		}
		else
			number_of_lifes_ = 0;
	}
}

void Enemy::checkCollisionWithMap(const float& Dx, const float& Dy)
{
	for (int i = y_ / 32; i < (y_ + height_) / 32; i++)
		for (int j = x_ / 32; j < (x_ + width_) / 32; j++)
			if (TileMap[i][j] == '0')
			{
				if (Dx > 0) {
					x_ = j * 32 - width_;
					current_state_ = states::kMovingLeft;
					dx_ *= -1.f;
				}
				else if (Dx < 0) {
					x_ = j * 32 + 32;
					current_state_ = states::kMovingRight;
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
	checkCollisionWithMap(dx_ * 2.f, 0.f);
	x_ += dx_ * time;

	collision_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f);
	sprite_.setPosition(x_ + width_ / 2.f, y_ + height_ / 2.f - 16.f);

	//Если здоровье меньше нуля
	if (number_of_lifes_ <= 0)
		was_died_ = true;

}
