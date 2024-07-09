#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	enum class type_of_action { MOVING_LEFT, MOVING_RIGHT, JUMPING, NO_ACTION};

	Player();

	//Getters
	bool getOnGround() const;
	sf::RectangleShape getCollision() const;
	sf::Sprite getSprite() const;
	type_of_action getCurrentAction() const;

	//Setters
	void setVelocityX(const float& velocity_x_);
	void setVelocityY(const float& velocity_y_);
	void setOnGround(const bool& on_ground_);
	void setCurrentAction(type_of_action action);
	void setPosition(const float& x, const float& y);

	//Methods of state
	bool isAlive(const float& lower_bound) const;
	void isFalling(const float& ground, const bool& thereIsBlockBelow);

	void changeSide(type_of_action action);

	void updateMovementX();

	void draw(sf::RenderWindow* window);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape collision;
	type_of_action currentAction = type_of_action::NO_ACTION;

	float velocity_x_ = 0.f;
	float velocity_y_ = 0.f;
	const float gravity_ = 1.f;

	bool on_ground_ = true;
	bool is_alive_ = true;
};

