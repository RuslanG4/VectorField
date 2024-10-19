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
		//_window.draw(node->nodeCostText);
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
		if (currentStartNode != -1)
		{
			drawPath(sf::Color::Blue);
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
		if (currentEndNode != -1)
		{
			drawPath(sf::Color::Blue);
		}
		nodeGrid[currentStartNode]->setState(NodeState::WALKABLE);
		currentStartNode = _nodeNumber;

	}
	nodeGrid[_nodeNumber]->setState(_updatedState);
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
	if (currentStartNode != -1 && currentEndNode != -1)
	{
		std::queue<Node*> nodeQueue;
		Node* prevNode = nullptr;

		nodeQueue.push(nodeGrid[currentEndNode]);
		nodeGrid[currentEndNode]->setMarked();

		nodeQueue.front()->setPrevious(prevNode);
		prevNode = nodeQueue.front();

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
					neighbour->setPrevious(prevNode);

					calculateVectors(neighbour);
					neighbour->calculatePoints();

					nodeQueue.push(neighbour);
				}
			}

			// dequeue the current node.
			nodeQueue.pop();
			if (nodeQueue.size() != 0) {
				prevNode = nodeQueue.front();
			}

		}
		drawPath(sf::Color::Yellow);
	}

}

void Grid::calculateVectors(Node* _currentNode)
{
	sf::Vector2f heading = _currentNode->getPrevious()->midPoint - _currentNode->midPoint;
	heading = Utility::unitVector2D(heading);
	_currentNode->pathVector = heading;
}

void Grid::drawPath(sf::Color _col)
{
	if (currentStartNode != -1 && currentEndNode != -1) {
		Node* endNode = nodeGrid[currentStartNode]->getPrevious();

		while (endNode != nullptr)
		{
			if(endNode->getPrevious() == nullptr)
			{
				endNode->pathVector = sf::Vector2f(0, 0);
				endNode->calculatePoints();
				break;
			}
			endNode->updatePath(_col);
			endNode = endNode->getPrevious();
		}
	}
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
