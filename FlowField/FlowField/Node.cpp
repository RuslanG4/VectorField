#include "Node.h"

void Node::setState(NodeState _state)
{
	switch (_state)
	{
	case NodeState::WALKABLE:
		drawableNode.setFillColor(sf::Color::Blue);
		currentState = _state;
		break;
	case NodeState::OBSTACLE:
		drawableNode.setFillColor(sf::Color::Black);
		currentState = _state;
		break;
	case NodeState::START:
		drawableNode.setFillColor(sf::Color::Green);
		currentState = _state;
		break;
	case NodeState::END:
		drawableNode.setFillColor(sf::Color::Red);
		currentState = _state;
		break;
	}
}
