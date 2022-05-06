#pragma once

#include "Wall.h"



class RayCaster
{
public:
	RayCaster();
	void render(sf::RenderWindow* window, std::vector<Wall>* walls, sf::Vector2f PlayerPos, float dir);
	float getDistance(Wall wall, sf::Vector2f PlayerPos, sf::Vector2f castPos);
private:
	float viewDistance = 1000;
	float fov = 40;
	sf::RectangleShape rect;
	sf::Vertex test[2];
	float getVectorAngle(sf::Vector2f vec);
	sf::Vector2u windowSize;
};

