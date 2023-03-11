#include "RayCaster.h"
#include <math.h>




RayCaster::RayCaster()
{
    test[0].color = sf::Color::Red;
    test[1].color = sf::Color::Red;
    mapMidPoint.x = 100;
    mapMidPoint.y = 100;
}

void RayCaster::render(sf::RenderWindow* window, std::vector<Wall>* walls, sf::Vector2f PlayerPos, float dir, float Ydir)
{
    
    //this->test[0].position = mapMidPoint;
    float lastVal = 0;
    float lastChange = 0;
    int a = 1;
    for (int x = 0; x < windowSize.x + 1; x += 1) {
        float dist = viewDistance;
        sf::Vector2f cast = sf::Vector2f(PlayerPos.x + viewDistance * cos((dir * 0.01745329 - fov * 0.01745329 / 2 + fov * 0.01745329 / windowSize.x * x)), PlayerPos.y + viewDistance * sin((dir - fov / 2 + fov / windowSize.x * x) * 0.01745329));
        for (Wall it : *walls) {
            float wallDist = getDistance(it, PlayerPos, cast);
            if (wallDist < dist && wallDist != 0) {
                dist = wallDist;
            }

        }

        float alpha = atan(abs(float(cast.y - PlayerPos.y) / float(cast.x - PlayerPos.x)));
        int xDir = (cast.x - PlayerPos.x) / abs(cast.x - PlayerPos.x);
        int yDir = (cast.y - PlayerPos.y) / abs(cast.y - PlayerPos.y);
        //this->test[1].position = sf::Vector2f(cos(alpha) * dist * xDir, sin(alpha) * dist * yDir) + mapMidPoint;
        //window->draw(test, 2, sf::Lines);

        if (dist != viewDistance) {
            float halfWin = (windowSize.x / 2);
            dist *= cos(abs((x - halfWin)) / halfWin * (fov * 0.01570796 / 2));





            float val = 1.3 - dist / (viewDistance)-(pow(x - windowSize.x / static_cast<float>(2), 2)) / (pow(0 - windowSize.x / static_cast<float>(2), 2));
            //val = (windowSize.y / (dist / 150)) / (windowSize.y);


            lastChange = dist - lastVal;

            val = 1 - abs(lastChange);

            if (val < 0.7)
                val = 0.7;
            else if (val > 1)
                val = 1;
            float yPos = abs(x - halfWin);
            this->rect.setPosition(x, (windowSize.y - windowSize.y / (dist / 15)) / 2 + Ydir * 0.1);
            this->rect.setSize(sf::Vector2f(3, windowSize.y / (dist / 15)));
            //this->rect.setSize(sf::Vector2f(2, dist));
            this->rect.setFillColor(sf::Color(255.0 * val, 255 * val, 255 * val, 255));
            window->draw(this->rect);
            lastVal = dist;
        }


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
