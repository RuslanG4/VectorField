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
	Node(NodeState _state, int _gridX, int _gridY, int size, sf::Font& _font) :
		currentState(_state),
		gridX(_gridX),
		gridY(_gridY),
		font(_font)
	{
		nodeCostText.setFont(font);
		nodeCostText.setFillColor(sf::Color::Black);
		nodeCostText.setString(std::to_string(999));
		nodeCostText.setCharacterSize(12);

		drawableNode.setSize(sf::Vector2f(size, size));
		drawableNode.setPosition(sf::Vector2f(gridX, gridY));
		drawableNode.setOutlineColor(sf::Color::Black);
		drawableNode.setOutlineThickness(2.f);

		nodeCostText.setPosition(sf::Vector2f(gridX, gridY));

		midPoint = sf::Vector2f(gridX + size / 2, gridY + size / 2);

		if(_state == NodeState::OBSTACLE)
		{
			drawableNode.setFillColor(sf::Color::Black);
			currentState = _state;
		} else
		{
			drawableNode.setFillColor(sf::Color::Green);
			currentState = _state;
		}
	};

	void addNeighbour(Node* t_cellId) { m_neighbours.push_back(t_cellId); }
	std::vector<Node*> getNeighbours() { return m_neighbours; };

	void setState(NodeState _state);
	NodeState getState() { return currentState; };

	void setID(int _id) { m_id = _id; };
	int getID() { return m_id; };

	void setMarked() { visited = !visited; };
	bool getMarked() { return visited; };

	void updateCost(int _cost) { cost = _cost + 1; nodeCostText.setString(std::to_string(cost));
	};
	int getCost() { return cost; };
	void resetCost() { cost = 999; nodeCostText.setString(std::to_string(cost));
	};
	void goalCost() {
		cost = 0;
		nodeCostText.setString(std::to_string(cost));
	};


	void updatePath(sf::Color _col);
	void calculatePoints();

	sf::RectangleShape drawableNode; //sfml render
	sf::Text nodeCostText;
	sf::Vector2f midPoint;
	sf::Vector2f pathVector;
	sf::VertexArray m_points;

private:
	int m_id;
	bool visited{ false };

	int cost{ 999 };

	std::vector<Node*> m_neighbours;

	int gridX; //position x
	int gridY; //position y

	NodeState currentState;

	sf::Font& font;
};

