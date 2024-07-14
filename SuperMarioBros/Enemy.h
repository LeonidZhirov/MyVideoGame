#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy : public Entity
{
public:
	enum class types_of_enemies { goomba = 0, koopa};

	Enemy(const sf::String& file, const float& x, const float& y, const float& width, const float& height, types_of_enemies type);

	types_of_enemies getType() const;

	bool getIsDeleted() const;

	void setIsDeleted(const bool& is_deleted);

	void checkCollisionWithMap(const float& Dx, const float& Dy);

	void update(const float& time);

private:
	types_of_enemies type_;
	bool is_deleted_;
};

