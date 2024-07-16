#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Item.h"

class Player : public Entity
{
public:
	enum class power_ups {kNoPowerUp = 0, kMushroomPowerUp, kFlowerPowerUp};

	Player(const sf::String& file, const float& x, const float& y, const float& width, const float& height);

	//Геттеры
	sf::View getPlayerView() const;
	bool getIsFalling() const;
	int getNumberOfLifes() const;

	void setIsAlive(const bool& is_alive);
	void setCollisionAndSprite(const float& width, const float& height);
	void setPowerUp(power_ups power_up);

	void control(const float& time);

	void interactionWithItems(Item& item);

	void checkPlayerCollisionWithMap(const float& Dx, const float& Dy);

	void updatePlayer(const float& time);

private:
	int player_score_;
	bool is_alive_, is_falling_;
	sf::View view_;
	power_ups current_power_up_;

};
