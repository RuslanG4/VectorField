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

	sf::CircleShape body;
	sf::Vector2f currVelocity;
};

