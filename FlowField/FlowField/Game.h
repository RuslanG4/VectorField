#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include"Constants.h"
#include "Grid.h"

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
	void processLeftMouse(sf::Event t_event);
	void processRightMouse(sf::Event t_event);
	void processMiddleMouse(sf::Event t_event);
	void processMouseUp(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void initialise();

	sf::Sprite m_appleSprite;
	sf::Texture m_appleTexture;

	sf::RenderWindow m_window; // main SFML window

	Grid myGrid;

	bool canClick = true;
	sf::Vector2f click;
};

#endif // !GAME_HPP