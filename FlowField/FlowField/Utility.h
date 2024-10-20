#pragma once
#include<SFML/Graphics.hpp>
namespace Utility
{
	const double PI = 3.141592653589793;
	const double DEG_TO_RADIAN = PI / 180.f;

	float magnitude(float x, float y);

	sf::Vector2f unitVector2D(sf::Vector2f vec);

	sf::Vector2f truncate(sf::Vector2f v, float const max);

	struct Vector2fCompare {
		bool operator()(const sf::Vector2f& lhs, const sf::Vector2f& rhs) const {
			if (lhs.x != rhs.x)
				return lhs.x < rhs.x;
			return lhs.y < rhs.y;
		}
	};

	float dotProduct(sf::Vector2f v1, sf::Vector2f v2);
};

