#pragma once
#include"Includes.h"

enum NodeState
{
	WALKABLE,
	OBSTACLE,
	START,
	END
};

class Node
{
public:
	Node(NodeState _state, int _gridX, int _gridY, int size) :
		currentState(_state),
		gridX(_gridX),
		gridY(_gridY)
	{
		drawableNode.setSize(sf::Vector2f(size, size));
		drawableNode.setPosition(sf::Vector2f(gridX, gridY));
		drawableNode.setOutlineColor(sf::Color::Black);
		drawableNode.setOutlineThickness(2.f);
		if(_state == NodeState::OBSTACLE)
		{
			drawableNode.setFillColor(sf::Color::Black);
			currentState = _state;
		} else
		{
			drawableNode.setFillColor(sf::Color::Blue);
			currentState = _state;
		}
	};

	void addNeighbour(int t_cellId) { m_neighbours.push_back(t_cellId); }
	std::vector<int>& neighbours() { return m_neighbours; }

	void setState(NodeState _state);
	void setID(int _id) { m_id = _id; };


	sf::RectangleShape drawableNode; //sfml render

private:
	int m_id;

	std::vector<int> m_neighbours;

	int gridX; //position x
	int gridY; //position y

	sf::Vector2f midPoint;

	NodeState currentState;
};

