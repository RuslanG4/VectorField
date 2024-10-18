#include "Game.h"

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "SFML Game" }
{
	initialise();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type) //user pressed mouse
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				processLeftMouse(newEvent);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				processRightMouse(newEvent);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				processMiddleMouse(newEvent);
			}
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseUp(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{

}

void Game::processLeftMouse(sf::Event t_event)
{
	if (canClick)
	{
		click.x = t_event.mouseButton.x / myGrid.getNodeSize();
		click.y = t_event.mouseButton.y / myGrid.getNodeSize();
		int nodeNum = click.x + (click.y * (SCREEN_HEIGHT / myGrid.getNodeSize()));
		myGrid.updateNodes(nodeNum, NodeState::START);
		canClick = false;
	}
}

void Game::processRightMouse(sf::Event t_event)
{
	if (canClick)
	{
		click.x = t_event.mouseButton.x / myGrid.getNodeSize();
		click.y = t_event.mouseButton.y / myGrid.getNodeSize();
		int nodeNum = click.x + (click.y * (SCREEN_HEIGHT / myGrid.getNodeSize()));
		myGrid.updateNodes(nodeNum, NodeState::END);
		canClick = false;
	}
}

void Game::processMiddleMouse(sf::Event t_event)
{
	if (canClick)
	{
		click.x = t_event.mouseButton.x / myGrid.getNodeSize();
		click.y = t_event.mouseButton.y / myGrid.getNodeSize();
		int nodeNum = click.x + (click.y * (SCREEN_HEIGHT / myGrid.getNodeSize()));
		myGrid.updateNodes(nodeNum, NodeState::OBSTACLE);
		canClick = false;
	}
}


void Game::processMouseUp(sf::Event t_event)
{
	canClick = true;
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	myGrid.drawGrid(m_window);
	m_window.display();
}

void Game::initialise()
{

}