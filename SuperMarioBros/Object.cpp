#include "Object.h"

//����������
Object::Object(const sf::String& file, const float& x, const float& y, const float& width, const float& height)
{
	x_ = x; y_ = y;
	width_ = width; height_ = height;
	dx_ = 0.f; dy_ = 0.f;
	current_frame_ = 0.f;
	file_ = file;

	//������ �������� �������
	collision_.setSize(sf::Vector2f(width_, height_));
	collision_.setOrigin(width_ / 2.f, height_ / 2.f);
	collision_.setFillColor(sf::Color::Green);

	//������ ������ �������
	texture_.loadFromFile("images/" + file_);
	sprite_.setTexture(texture_);
	sprite_.setOrigin(width_ / 2.f, height_ / 2.f);
	sprite_.setScale(2.f, 2.f);
}

//��������� ������
//�������
float Object::getDx() const
{
	return dx_;
}

float Object::getDy() const
{
	return dy_;
}

sf::FloatRect Object::getCollisionRect() const
{
	return collision_.getGlobalBounds();
}

//�������
void Object::setDx(const float& dx)
{
	dx_ = dx;
}

void Object::setDy(const float& dy)
{
	dy_ = dy;
}

//���������
void Object::draw(sf::RenderWindow& window)
{
	window.draw(collision_);
	window.draw(sprite_);
}

//���������� ������
void Object::doObjectAnimations(const float& time, const int& number_of_frames)
{
	current_frame_ += 0.005 * time;

	if (current_frame_ > number_of_frames)
		current_frame_ -= number_of_frames;
}
