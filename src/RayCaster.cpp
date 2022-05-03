#include "../include/RayCaster.h"




RayCaster::RayCaster()
{
    test[0].color = sf::Color::Red;
    test[1].color = sf::Color::Red;
}

void RayCaster::render(sf::RenderWindow* window, std::vector<Wall>* walls, sf::Vector2f PlayerPos, float dir)
{
    this->windowSize = window->getSize();
    this->test[0].position = PlayerPos;
    float lastVal = 0;
    for (int x = 0; x < window->getSize().x; x += 2) {
        float dist = viewDistance;
        sf::Vector2f cast = sf::Vector2f(PlayerPos.x + viewDistance * cos((dir * 0.01745329 - fov * 0.01745329 / 2 + fov * 0.01745329 / window->getSize().x * x)), PlayerPos.y + viewDistance * sin((dir - fov / 2 + fov / window->getSize().x * x) * 0.01745329));
        for (Wall it : *walls) {
            float wallDist = this->getDistance(it, PlayerPos, cast);
            if (wallDist < dist && wallDist != 0) {
                dist = wallDist;
            }

        }
        float alpha = atan(abs(float(cast.y - PlayerPos.y) / float(cast.x - PlayerPos.x)));
        int xDir = (cast.x - PlayerPos.x) / abs(cast.x - PlayerPos.x);
        int yDir = (cast.y - PlayerPos.y) / abs(cast.y - PlayerPos.y);
        this->test[1].position = sf::Vector2f(PlayerPos.x + cos(alpha) * dist * xDir, PlayerPos.y + sin(alpha) * dist * yDir);

        if (dist == viewDistance) { dist = 0; }

        window->draw(test, 2, sf::Lines);
        float val = 1 - dist / viewDistance;

        this->rect.setPosition(x, (window->getSize().y - window->getSize().y/(dist / 15))/2);
        this->rect.setSize(sf::Vector2f(2, window->getSize().y / (dist / 15)));
        this->rect.setFillColor( sf::Color(255.0 * val, 255 * val, 255 * val, 255));
        //std::cout << (abs(lastVal - dist)) << "\n";
        window->draw(this->rect);
        lastVal = dist;
    }

}


float RayCaster::getDistance(Wall wall, sf::Vector2f PlayerPos, sf::Vector2f castPos)
{



    float slope1 = (wall.start.y - wall.end.y) / (wall.end.x - wall.start.x);
    if (std::isinf(slope1))
    {
        slope1 = 99999999;

    }
    float xPos1 = PlayerPos.x - wall.start.x;
    float xPos2 = castPos.x - wall.start.x;
    bool firstY = (wall.start.y - (xPos1 * slope1) > PlayerPos.y);
    bool secondY = (wall.start.y - (xPos2 * slope1) > castPos.y);
    if (firstY != secondY)
    {
        this->test[1].position = sf::Vector2f(10000, 10000);
        float slope2 = (PlayerPos.y - castPos.y) / (castPos.x - PlayerPos.x);
        if (std::isinf(slope2))
        {
            slope2 = 99999999;

        }
        xPos1 = wall.start.x - PlayerPos.x;
        xPos2 = wall.end.x - PlayerPos.x;
        firstY = (PlayerPos.y - (xPos1 * slope2) > wall.start.y);
        secondY = (PlayerPos.y - (xPos2 * slope2) > wall.end.y);
        if (firstY != secondY)
        {

            float x = (-(PlayerPos.y - wall.start.y) + (slope2 * -(PlayerPos.x - wall.start.x))) / (slope2 - slope1);
            float y = x * slope1;
            x = wall.start.x - x;
            y = wall.start.y + y;
            //this->test[1].position = sf::Vector2f(x, y);

            //std::cout << this->test[1].position.x * this->test[1].position.x + this->test[1].position.y * this->test[1].position.y << "\n";
            return sqrt((x - PlayerPos.x) * (x - PlayerPos.x) + (y - PlayerPos.y) * (y - PlayerPos.y));
        }
    }
    //this->test[1].position = castPos;
    return viewDistance;
}

float RayCaster::getVectorAngle(sf::Vector2f vec)
{
    float alpha = atan( float(vec.y) / float(vec.x));
    return alpha;
}
