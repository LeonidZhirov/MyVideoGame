#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Entity
{
public:
	enum class states { kStays = 0, kLeft, kRight, kJumps };

	Entity(const sf::String& file, const float& x, const float& y, const float& width, const float& height);

	sf::FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return sf::FloatRect(x_, y_, width_, height_);//эта ф-ция нужна для проверки столкновений 
	}

	float getDx() const;
	float getDy() const;
	sf::FloatRect getRect() const; 
	bool wasDied() const;
	bool isOnGround() const;

	void setDx(const float& dx);
	void setDy(const float& dy);
	void setNumberOfLifes(const float& number_of_lifes);

	void draw(sf::RenderWindow& window);

protected:
	float x_, y_, width_, height_, dx_, dy_, speed_;
	int number_of_lifes_;
	bool was_died_, is_moving_, on_ground_;
	float current_frame_;


	sf::Texture texture_;
	sf::Sprite sprite_;
	sf::RectangleShape collision_;

	states current_state_;

	//void updateEntity(const float& time);

	void doAnimations(const float& time);
};

