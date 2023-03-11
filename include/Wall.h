#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Wall
{
public:
	Wall(sf::Vector2f start, sf::Vector2f end);
	virtual ~Wall();
	sf::Vector2f start;
	sf::Vector2f end;
	sf::Vertex wall[2];
	void render(sf::RenderWindow* window, sf::Vector2f offset);
};

