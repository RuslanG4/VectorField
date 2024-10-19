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
	myGrid = new Grid(myFont);
	for (int i = 0; i < 15; i++)
	{
		int x = (std::rand() % 50 + 1);
		int y = (std::rand() % 50 + 1);
		int currentNode = x * y;

		balls[i].body.setPosition(myGrid->getNode(currentNode));
	}
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
			if(sf::Event::MouseButtonPressed == newEvent.type)
			{
				processMouseDown(newEvent);
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

void Game::processMouseDown(sf::Event t_event)
{
	if (canClick)
	{
		click.x = t_event.mouseButton.x / myGrid->getNodeSize();
		click.y = t_event.mouseButton.y / myGrid->getNodeSize();
		int nodeNum = click.x + (click.y * (SCREEN_HEIGHT / myGrid->getNodeSize()));

		switch (t_event.mouseButton.button)
		{
		case sf::Mouse::Left:
			myGrid->updateNodes(nodeNum, NodeState::START);
			player.body.setPosition(myGrid->getNode(nodeNum));
			myGrid->resetNodes();
			myGrid->pathFind();
			break;
		case sf::Mouse::Right:
			myGrid->updateNodes(nodeNum, NodeState::END);
			myGrid->resetNodes();
			myGrid->pathFind();
			startJourney = true;
			break;
		case sf::Mouse::Middle:
			myGrid->drawPath(sf::Color::Blue);
			myGrid->updateNodes(nodeNum, NodeState::OBSTACLE);
			myGrid->resetNodes();
			myGrid->pathFind();
			break;
		}

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
	if(startJourney)
	{
		//updatePlayer();
		updateBall();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	myGrid->drawGrid(m_window);
	player.render(m_window);
	/*for (int i = 0; i < 15; i++)
	{
		balls[i].render(m_window);
	}*/
	m_window.display();
}

void Game::initialise()
{
	if(!myFont.loadFromFile(FONT_PATH))
	{
		std::cout << "error loading font";
	}
	
}

void Game::updatePlayer()
{
	for (int i = 0; i < 15; i++) {
		sf::Vector2f currentPos;
		currentPos.x = static_cast<int>(balls[i].body.getPosition().x / 20);
		currentPos.y = static_cast<int>(balls[i].body.getPosition().y / 20);
		int currentNode = currentPos.x + (currentPos.y * (SCREEN_HEIGHT / 20));

		sf::Vector2f distVec = myGrid->getNode(currentNode) - balls[i].body.getPosition();
		float dist = Utility::magnitude(distVec.x, distVec.y);

		if (dist < 1 )
		{
			balls[i].currVelocity = myGrid->getNodeVelocity(currentNode);
		}

		balls[i].update();
	}
}

void Game::updateBall()
{
	sf::Vector2f currentPos;
	currentPos.x = static_cast<int>(player.body.getPosition().x / 20);
	currentPos.y = static_cast<int>(player.body.getPosition().y / 20);
	int currentNode = currentPos.x + (currentPos.y * (SCREEN_HEIGHT / 20));

	sf::Vector2f distVec = myGrid->getNode(currentNode) - player.body.getPosition();
	float dist = Utility::magnitude(distVec.x, distVec.y);

	if (dist < 1)
	{
		player.currVelocity = myGrid->getNodeVelocity(currentNode);
	}

	player.update();
}


