#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
public:
	Player(const sf::String& file, const float& x, const float& y, const float& width, const float& height);

	//Геттеры
	sf::View getPlayerView() const;

	void setIsAlive(const bool& is_alive);

	void control(const float& time);

	void checkCollisionWithMap(const float& Dx, const float& Dy);

	void updatePlayer(const float& time);

private:
	int player_score_;
	bool is_alive_;
	sf::View view_;
};
