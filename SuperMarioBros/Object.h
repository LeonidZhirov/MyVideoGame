#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Object
{
public:
	//�����������
	Object(const sf::String& file, const float& x, const float& y, const float& width, const float& height);

	//�������
	float getDx() const;
	float getDy() const;
	sf::FloatRect getCollisionRect() const;

	//�������
	void setDx(const float& dx);
	void setDy(const float& dy);

	//���������
	void draw(sf::RenderWindow& window);

protected:
	float x_, y_, width_, height_, dx_, dy_, current_frame_;

	sf::Texture texture_;
	sf::Sprite sprite_;
	sf::RectangleShape collision_;
	sf::String file_;

	//�������� �������
	void doObjectAnimations(const float& time, const int& number_of_frames);
};

