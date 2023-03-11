#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "RayCaster.h"


struct KeyMapWASD {
	bool W;
	bool A;
	bool S;
	bool D;
};

struct KeyMap {
	bool Left;
	bool Right;
};

class MainLoop
{
public:
	MainLoop();
	virtual ~MainLoop();

	//Called by main every frame
	void update();
	void render();

	// Accessors
	const bool running() const;

private:
	//-Window-//
	sf::RenderWindow* window;

	//-Event-//
	sf::Event event;


	//-initilize-//
	void initVariables();
	void initWindow();
	void initGameObjects();

	//-Events-//
	void pollEvents();



	//--Private Variables --//

	//-inputs-//
	sf::Vector2i MousePosition;
	bool leftMouseButton;



	KeyMapWASD keyMapWASD;
	KeyMap keyMap;
	float sensitivity;

	//-timing-fps-//
	float fps;
	sf::Clock clock;
	sf::Time previousTime;
	sf::Time currentTime;


	//Elements

	RayCaster rayCaster;




	//movement
	sf::Vector2f PlayerPos;

	float lookDir;
	float lookDirY;

	float speed;

	//Background
	sf::RectangleShape top;
	sf::RectangleShape bottom;

	//Walls
	std::vector<Wall> wallList;

};
