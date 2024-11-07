#include "Ball.h"

Ball::Ball()
{
	init();
}

void Ball::update()
{
	sf::Vector2f movement = body.getPosition() + (currVelocity * 1.25f);
	body.setPosition(movement);
}

void Ball::render(sf::RenderWindow& window)
{
	window.draw(body);
}

void Ball::init()
{
	body.setRadius(8.f);
	body.setOrigin(8, 8);
	body.setOutlineColor(sf::Color::Yellow);
	body.setOutlineThickness(2);
	body.setFillColor(sf::Color::Magenta);
}

