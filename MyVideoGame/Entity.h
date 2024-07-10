#pragma once
#include "Object.h"

class Entity :
    public Object
{
public:
    enum class type_of_action { MOVING_LEFT, MOVING_RIGHT, JUMPING, NO_ACTION };

	Entity(const sf::Vector2f& position, const sf::Vector2f& collisionSize, const sf::Vector2f& collisionScale, const sf::Vector2f& spriteScale,
		const std::string& textureName, const int& x, const int& y, const int& width, const int& height)
        : Object(position, collisionSize, collisionScale, spriteScale, textureName, x, y, width, height) {};

	//Getters
	bool getOnGround() const;
	type_of_action getCurrentAction() const;

	//Setters
	void setVelocityX(const float& velocity_x_);
	void setVelocityY(const float& velocity_y_);
	void setOnGround(const bool& on_ground_);
	void setCurrentAction(type_of_action action);

	//Methods of state
	bool isAlive(const float& lower_bound) const;
	void isFalling(const float& obstacle, const bool& thereIsBlockBelow);
	bool checkCollisions(std::shared_ptr<Entity> entity) const;

	void changeSide(type_of_action action);

	void control();

	void updateMovementX();

protected:
    type_of_action currentAction = type_of_action::NO_ACTION;

    float velocity_x_ = 0.f;
    float velocity_y_ = 0.f;
    const float gravity_ = 1.f;

    bool on_ground_ = false;
    bool is_alive_ = true;
	bool is_moving = false;
};

