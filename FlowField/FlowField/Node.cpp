#include "Node.h"

void Node::setState(NodeState _state)
{
	switch (_state)
	{
	case NodeState::WALKABLE:
		drawableNode.setFillColor(sf::Color::Green);
		currentState = _state;
		break;
	case NodeState::OBSTACLE:
		drawableNode.setFillColor(sf::Color::Black);
		currentState = _state;
		break;
	case NodeState::START:
		drawableNode.setFillColor(sf::Color::Blue);
		currentState = _state;
		break;
	case NodeState::END:
		drawableNode.setFillColor(sf::Color::Red);
		currentState = _state;
		break;
	}
}

void Node::updatePath(sf::Color _col)
{
	drawableNode.setFillColor(_col);
}

void Node::calculatePoints()
{
	m_points.setPrimitiveType(sf::Lines); //sets line
	m_points.clear(); //only draws one line

	sf::Vertex m_start;
	m_start.color = sf::Color::Black;
	m_start.position = midPoint;    //start line at origin of ball
	m_points.append(m_start);

	sf::Vertex newVertrex;
	newVertrex.color = sf::Color::Black;
	newVertrex.position.x = (pathVector.x * 10) + midPoint.x;    //end line
	newVertrex.position.y = (pathVector.y * 10) + midPoint.y;
	m_points.append(newVertrex);
}
