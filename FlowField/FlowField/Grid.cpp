#include "Grid.h"

void Grid::createGrid(sf::Font& _font)
{
	int rows = SCREEN_HEIGHT / gridNodeSize;  //identifies the amount of rows
	int cols = SCREEN_WIDTH / gridNodeSize;  //identifies the amount of columns
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			nodeGrid.push_back(new Node(NodeState::WALKABLE, j * gridNodeSize, i * gridNodeSize, gridNodeSize, _font)); //pushes a new node with passable and x and y and gives id
		}
	}
	//Setup id's first
	int max = rows * cols;
	for (int i = 0; i < max; i++)
	{
		nodeGrid[i]->setID(i);
		addNeighbours(i);
	}
};

void Grid::drawGrid(sf::RenderWindow& _window)
{
	for(auto node : nodeGrid)
	{
		_window.draw(node->drawableNode);
		_window.draw(node->nodeCostText);
		_window.draw(node->m_points);
	}
}

void Grid::updateNodes(int _nodeNumber, NodeState _updatedState)
{
	if(currentEndNode != _nodeNumber && _updatedState == NodeState::END)
	{
		if(currentEndNode == -1)
		{
			currentEndNode = _nodeNumber;
		}
		nodeGrid[currentEndNode]->setState(NodeState::WALKABLE);
		currentEndNode = _nodeNumber;
	}
	else if(currentStartNode != _nodeNumber && _updatedState == NodeState::START)
	{
		if (currentStartNode == -1)
		{
			currentStartNode = _nodeNumber;
		}
		nodeGrid[currentStartNode]->setState(NodeState::WALKABLE);
		currentStartNode = _nodeNumber;

	}
	nodeGrid[_nodeNumber]->setState(_updatedState);
	resetNodes();
}

void Grid::addNeighbours(int _currentNodeId)
{
	const int MAX_ROWS = (SCREEN_HEIGHT / gridNodeSize);
	const int MAX_COLS = (SCREEN_WIDTH / gridNodeSize);

	int row = _currentNodeId / MAX_COLS;
	int col = _currentNodeId % MAX_COLS;
	int neighbourIndex = -1;

	//This neighbour algoritihim prioritises vertical/hjorizontal then diagonal
	std::array<int, 9> directionOrder
	{
		1,3,5,7,0,2,6,8 //exclude 4 since that is our cell
	};
	for (auto& direction : directionOrder) {

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < MAX_ROWS && n_col >= 0 && n_col < MAX_COLS) {
			neighbourIndex = n_row * MAX_COLS + n_col;
			nodeGrid[_currentNodeId]->addNeighbour(nodeGrid[neighbourIndex]);
		}
	}
}

void Grid::pathFind()
{
	if (currentEndNode != -1)
	{
		std::queue<Node*> nodeQueue;

		nodeGrid[currentEndNode]->goalCost();
		nodeQueue.push(nodeGrid[currentEndNode]);
		nodeGrid[currentEndNode]->setMarked();

		// loop through the queue while there are nodes in it.
		while (nodeQueue.size() != 0)
		{
			// add all of the child nodes that have not been 
			// marked into the queue
			auto neighbours = nodeQueue.front()->getNeighbours();

			for (auto neighbour : neighbours)
			{
				if (neighbour->getMarked() == false && neighbour->getState() != NodeState::OBSTACLE)
				{
					// mark the node and add it to the queue.
					neighbour->setMarked();
					neighbour->updateCost(nodeQueue.front()->getCost());

					float normCost = static_cast<float>(neighbour->getCost()) / 80.0f;
					sf::Color color = sf::Color(
						static_cast<sf::Uint8>(255 * normCost),  // Red
						static_cast<sf::Uint8>(255 * (1.0f - normCost)),  // Green
						0);  // No Blue

					neighbour->drawableNode.setFillColor(color);
					nodeQueue.push(neighbour);
				}
			}
			// dequeue the current node.
			nodeQueue.pop();
		}
		for (auto node : nodeGrid) {
			node->pathVector = calculateVectors(node);
			node->calculatePoints();
		}
		if (currentStartNode != -1) {
			drawPath(sf::Color::Yellow);
		}
	}

}

sf::Vector2f Grid::calculateVectors(Node* _node)
{
	sf::Vector2f bestDirection(0.0f, 0.0f);
	int lowestCost = _node->getCost();

	for(auto neighbour : _node->getNeighbours())
	{
		if(neighbour->getCost() < lowestCost)
		{
			lowestCost = neighbour->getCost();

			bestDirection.x = neighbour->getID() % 50 - _node->getID() % 50;
			bestDirection.y = neighbour->getID() / 50 - _node->getID() / 50;
		}
	}
	if (bestDirection.x != 0 || bestDirection.y != 0) {
		bestDirection = Utility::unitVector2D(bestDirection);
	}

	return bestDirection;
}

void Grid::drawPath(sf::Color _col)
{
		nodeGrid[currentStartNode]->drawableNode.setFillColor(sf::Color::Blue);
		int currentNode = currentStartNode;
		sf::Vector2f currentNodeVector = nodeGrid[currentStartNode]->pathVector;

		//calculateVectors

		while (currentNodeVector != sf::Vector2f(0,0))
		{
			if(currentNodeVector == sf::Vector2f(1,0))
			{
				currentNode = currentNode + 1;
			}
			else if(currentNodeVector == sf::Vector2f(0, 1))
			{
				currentNode = currentNode + 50;
			}
			else if (currentNodeVector == sf::Vector2f(-1, 0))
			{
				currentNode = currentNode - 1;
			}
			else if (currentNodeVector == sf::Vector2f(0, -1))
			{
				currentNode = currentNode - 50;
			}
			else if((currentNodeVector.x < 1 && currentNodeVector.x > 0) && (currentNodeVector.y < 1 && currentNodeVector.y > 0))
			{
				currentNode = currentNode + 51;
			}
			else if ((currentNodeVector.x < 0) && (currentNodeVector.y < 1 && currentNodeVector.y > 0))
			{
				currentNode = currentNode + 49;
			}
			else if ((currentNodeVector.x < 0) && (currentNodeVector.y <0))
			{
				currentNode = currentNode -51;
			}
			else if ((currentNodeVector.x < 1 && currentNodeVector.x > 0) && (currentNodeVector.y <0))
			{
				currentNode = currentNode -49;
			}

			nodeGrid[currentNode]->drawableNode.setFillColor(sf::Color::Yellow);
			currentNodeVector = nodeGrid[currentNode]->pathVector;

		}
		nodeGrid[currentEndNode]->drawableNode.setFillColor(sf::Color::Red);
}

void Grid::resetNodes()
{
	for(auto node : nodeGrid)
	{
		if(node->getMarked())
		{
			node->setMarked();
		}
		node->resetCost();
	}
}
