#include "mainLoop.h"
#include "Wall.h"
#include "RayCaster.h"

#include <math.h>

MainLoop::MainLoop()
{
    // initialize
    this->initVariables();
    this->initWindow();
    this->initGameObjects();

}

MainLoop::~MainLoop()
{
    delete this->window;
}

// Accessors
const bool MainLoop::running() const
{
    return this->window->isOpen();
}

//------Functions------//
//---Voids---//

//--Events--//
void MainLoop::pollEvents()
{

    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            else if (this->event.key.code == sf::Keyboard::X)
                this->window->close();
            else if (this->event.key.code == sf::Keyboard::W) {
                
                this->keyMapWASD.W = true;
            }
            else if (this->event.key.code == sf::Keyboard::A)
            {
                this->keyMapWASD.A = true;
            }
            else if (this->event.key.code == sf::Keyboard::S)
            {
                this->keyMapWASD.S = true;
            }
            else if (this->event.key.code == sf::Keyboard::D)
            {

                this->keyMapWASD.D = true;
            }
            else if (this->event.key.code == sf::Keyboard::Left)
            {
                keyMap.Left = true;
            }
            else if (this->event.key.code == sf::Keyboard::Right)
            {
                keyMap.Right = true;
            }
            break;
        case sf::Event::KeyReleased:
            if (this->event.key.code == sf::Keyboard::W)
                this->keyMapWASD.W = false;
            else if (this->event.key.code == sf::Keyboard::A)
                this->keyMapWASD.A = false;
            else if (this->event.key.code == sf::Keyboard::S)
                this->keyMapWASD.S = false;
            else if (this->event.key.code == sf::Keyboard::D)
                this->keyMapWASD.D = false;
            else if (this->event.key.code == sf::Keyboard::Left)
                keyMap.Left = false;

            else if (this->event.key.code == sf::Keyboard::Right)
                keyMap.Right = false;

            break;
        case sf::Event::MouseButtonPressed:
            if (this->event.key.code == sf::Mouse::Left)

                leftMouseButton = true;
            break;
        case sf::Event::MouseButtonReleased:
            if (this->event.key.code == sf::Mouse::Left)
                leftMouseButton = false;
            break;
        }


    }

    // update Mouse Position
    MousePosition = sf::Mouse::getPosition(*this->window);
    sf::Mouse::setPosition(sf::Vector2i(0, 0),*this->window);


    // calc FPS
    currentTime = clock.getElapsedTime();
    fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
    previousTime = currentTime;


    if (keyMapWASD.W)
        this->PlayerPos += sf::Vector2f(cos(lookDir * 0.01745329) * speed, sin(lookDir * 0.01745329) * speed);
    if (keyMapWASD.A)
        this->PlayerPos += sf::Vector2f(sin(lookDir * 0.01745329) * speed, cos(lookDir * 0.01745329) * -speed);
    if (keyMapWASD.S)
        this->PlayerPos += sf::Vector2f(cos(lookDir * 0.01745329) * -speed, sin(lookDir * 0.01745329) * -speed);
    if (keyMapWASD.D)
        this->PlayerPos += sf::Vector2f(sin(lookDir * 0.01745329) * -speed, cos(lookDir * 0.01745329) * speed);

    lookDir += MousePosition.x * sensitivity;
    lookDirY -= MousePosition.y * sensitivity * 300;
    int ad = 600;
    if (lookDirY > 5 * ad) {
        lookDirY = 5 * ad;
    }
    else if (lookDirY < -5 * ad) {
        lookDirY = -5 * ad;
    }
    //std::cout << lookDirY << "\n";
    bottom.setPosition(0, this->window->getSize().y / 2 + lookDirY / 10.0);
    /*
    * was used to look around with left and right
    if (keyMap.Left) {
        this->lookDir -= 0.6;
        if (lookDir < 0)
            lookDir = 360;
    }
    if (keyMap.Right) {
        this->lookDir += 0.6;
        if (lookDir > 360)
            lookDir = 0;
    }
*/
}

//--initialize--//
void MainLoop::initVariables()
{

    this->window = nullptr;
    // if (!font.loadFromFile("../assets/font.ttf"))
    // {
    //     sf::err() << "Couldn't load font\n";
    // }

    previousTime = clock.getElapsedTime();
    speed = 0.3f;

    this->keyMapWASD.W = false;
    this->keyMapWASD.A = false;
    this->keyMapWASD.S = false;
    this->keyMapWASD.D = false;


    
}

void MainLoop::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    this->window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Main", sf::Style::Close, settings);
    this->window->setFramerateLimit(165);

    rayCaster.windowSize = this->window->getSize();
}

void MainLoop::initGameObjects()
{

    top.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
    bottom.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));

    top.setPosition(0, 0);
    bottom.setPosition(0, this->window->getSize().y / 2);

    top.setFillColor(sf::Color(113, 126, 255));
    bottom.setFillColor(sf::Color(119, 221, 119));

    //create Walls
    Wall wall1(sf::Vector2f(0,0), sf::Vector2f(0,50));
    wallList.push_back(wall1);
    Wall wall2(sf::Vector2f(0, 0), sf::Vector2f(300, 0));
    wallList.push_back(wall2);
    
    Wall wall3(sf::Vector2f(0, 50), sf::Vector2f(350, 50));
    wallList.push_back(wall3);

    Wall wall4(sf::Vector2f(350, 50), sf::Vector2f(350, 0));
    wallList.push_back(wall4);
   
    Wall wall5(sf::Vector2f(320, 0), sf::Vector2f(350, 0));
    wallList.push_back(wall5);
 
    Wall wall6(sf::Vector2f(300, 0), sf::Vector2f(300, -10));
    wallList.push_back(wall6);
    Wall wall7(sf::Vector2f(320, 0), sf::Vector2f(320, -10));
    wallList.push_back(wall7);
    Wall wall8(sf::Vector2f(320, -10), sf::Vector2f(370, -10));
    wallList.push_back(wall8);
    Wall wall9(sf::Vector2f(300, -10), sf::Vector2f(250, -10));
    wallList.push_back(wall9);
    Wall wall10(sf::Vector2f(250, -10), sf::Vector2f(250, -110));
    wallList.push_back(wall10);
    Wall wall11(sf::Vector2f(250, -110), sf::Vector2f(370, -110));
    wallList.push_back(wall11);
    Wall wall12(sf::Vector2f(370, -10), sf::Vector2f(370, -110));
    wallList.push_back(wall12);

    PlayerPos = sf::Vector2f(100, 100);
    lookDir = 0;
    sensitivity = 0.1;
}

//--Update--//

//-Called by main--//
void MainLoop::update()
{
    // Events
    this->pollEvents();

}


//--render--// -> Called by main
void MainLoop::render()
{
    //std::cout << fps << "\n";
    //  clear screen
    this->window->clear(sf::Color(60, 60, 60, 255));

    //Background
    
    
    this->window->draw(this->top);
    this->window->draw(this->bottom);

    this->rayCaster.render(this->window, &wallList, PlayerPos, lookDir, lookDirY);

    /*
    for (auto it : wallList) {
        it.render(this->window, -PlayerPos + sf::Vector2f(100,100));
    }
*/

    // display screen
    this->window->display();
}