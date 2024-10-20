#pragma once
#include"Includes.h"
class Ball
{
public:
	Ball();
	~Ball() {};
	void update();
	void render(sf::RenderWindow& window);
	void init();
	void seek(sf::Vector2f target, sf::Vector2f flowVel);

	sf::CircleShape body;
	sf::Vector2f currVelocity;
};

