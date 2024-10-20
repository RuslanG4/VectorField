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
	body.setRadius(4.f);
	body.setOrigin(4, 4);
	body.setFillColor(sf::Color::Magenta);
}

