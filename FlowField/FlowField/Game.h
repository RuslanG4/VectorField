#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include"Constants.h"
#include "Grid.h"
#include"Ball.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void initialise();

	sf::Sprite m_appleSprite;
	sf::Texture m_appleTexture;

	sf::Font myFont;

	sf::RenderWindow m_window; // main SFML window

	Grid* myGrid;

	bool canClick = true;
	sf::Vector2f click;

	Ball player;

	Ball balls[15];

	bool startJourney;
	void updatePlayer();
	void updateBall();
};

#endif // !GAME_HPP