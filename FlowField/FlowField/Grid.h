#pragma once
#include"Includes.h"
#include"Node.h"

class Grid
{
public:
	Grid(sf::Font& _font)
	{
		createGrid(_font);
	};
	void createGrid(sf::Font& _font);
	void drawGrid(sf::RenderWindow& _window);
	void updateNodes(int _nodeNumber, NodeState _updatedState);
	void addNeighbours(int _currentNodeId);
	int const getNodeSize() const { return gridNodeSize; };

	void pathFind();
	void calculateVectors(Node* _currentNode);
	void drawPath(sf::Color _col);
	void resetNodes();

	sf::Vector2f getNodeVelocity(int _NodeNum) { return nodeGrid[_NodeNum]->pathVector; };
	sf::Vector2f getNode(int _NodeNum) { return nodeGrid[_NodeNum]->midPoint; };
private:
	std::vector<Node*> nodeGrid;

	int currentStartNode{ -1 };
	int currentEndNode{ -1 };

	int gridNodeSize = 20; //each tile is 20x 20 
};

