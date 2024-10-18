#include "Grid.h"

void Grid::drawGrid(sf::RenderWindow& _window)
{
	for(auto node : nodeGrid)
	{
		_window.draw(node.drawableNode);
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
		nodeGrid[currentEndNode].setState(NodeState::WALKABLE);
		currentEndNode = _nodeNumber;
	}
	else if(currentStartNode != _nodeNumber && _updatedState == NodeState::START)
	{
		if (currentStartNode == -1)
		{
			currentStartNode = _nodeNumber;
		}
		nodeGrid[currentStartNode].setState(NodeState::WALKABLE);
		currentStartNode = _nodeNumber;
	}
	nodeGrid[_nodeNumber].setState(_updatedState);
}
