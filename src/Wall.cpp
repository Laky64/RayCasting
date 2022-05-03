#include "../include/Wall.h"

Wall::Wall(sf::Vector2f start, sf::Vector2f end)
{
	this->start = start;
	this->end = end;
	wall[0].color = sf::Color::Green;
	wall[1].color = sf::Color::Green;

	wall[0].position = start;
	wall[1].position = end;
}

Wall::~Wall()
{
}

void Wall::render(sf::RenderWindow* window)
{
	window->draw(wall, 2, sf::Lines);
}
