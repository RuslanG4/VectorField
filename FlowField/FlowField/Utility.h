#pragma once
#include<SFML/Graphics.hpp>
namespace Utility
{
	const double PI = 3.141592653589793;
	const double DEG_TO_RADIAN = PI / 180.f;

	float magnitude(float x, float y);

	sf::Vector2f unitVector2D(sf::Vector2f vec);

	sf::Vector2f truncate(sf::Vector2f v, float const max);

	float dotProduct(sf::Vector2f v1, sf::Vector2f v2);
};

