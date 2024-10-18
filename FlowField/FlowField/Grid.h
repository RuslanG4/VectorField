#pragma once
#include"Includes.h"
#include"Node.h"

class Grid
{
public:
	Grid()
	{
		createGrid();
	};
	void createGrid() //creates grid, use on initialise 
	{
		int rows = SCREEN_HEIGHT / gridNodeSize;  //identifies the amount of rows
		int cols = SCREEN_WIDTH / gridNodeSize;  //identifies the amount of columns
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				nodeGrid.push_back(Node(NodeState::WALKABLE, j * gridNodeSize, i * gridNodeSize, gridNodeSize)); //pushes a new node with passable and x and y and gives id
			}
		}

	};
	void drawGrid(sf::RenderWindow& _window);
	void updateNodes(int _nodeNumber, NodeState _updatedState);
	int const getNodeSize() { return gridNodeSize; };
private:
	std::vector<Node> nodeGrid;

	int currentStartNode{ -1 };
	int currentEndNode{ -1 };

	int gridNodeSize = 20; //each tile is 20x 20 
};

