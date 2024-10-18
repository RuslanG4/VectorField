#include "Node.h"

void Node::setState(NodeState _state)
{
	switch (_state)
	{
	case NodeState::WALKABLE:
		drawableNode.setFillColor(sf::Color::Blue);
		break;
	case NodeState::OBSTACLE:
		drawableNode.setFillColor(sf::Color::Black);
		break;
	case NodeState::START:
		drawableNode.setFillColor(sf::Color::Green);
		break;
	case NodeState::END:
		drawableNode.setFillColor(sf::Color::Red);
		break;
	}
}
