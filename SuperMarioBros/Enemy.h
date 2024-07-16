#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player;

class Enemy : public Entity
{
public:
	enum class types_of_enemies { goomba = 0, koopa };
	enum class koopa_states { not_koopa = 0, turtle, shell };

	Enemy(const sf::String& file, const float& x, const float& y, const float& width, const float& height, types_of_enemies type, koopa_states koopa_state);

	types_of_enemies getType() const;

	bool getIsDeleted() const;
	koopa_states getKoopaState() const;

	void interactionWithPlayer(Player& player);
	void interactionWithOtherEnemies(Enemy& enemy);

	void checkCollisionWithMap(const float& Dx, const float& Dy);

	void update(const float& time);

private:
	types_of_enemies type_;
	koopa_states koopa_state_;
	bool is_deleted_;
	unsigned interactions_with_player_;
};

