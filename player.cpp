
#include <stdio.h>
#include <iostream>
#include <cmath>
// #include <math.h>
#include <vector>

#include "utils.hpp"
#include "CONSTANT.hpp"
#include "ray.hpp"
#include "player.hpp"

#include "coord.hpp"
Player::Player(SDL_Renderer *renderer, std::string nom, int hp, float x, float y) : renderer(renderer), nom(nom), hp(hp), x(x), y(y)
{
    this->rectPlayer.x = this->x;
    this->rectPlayer.y = this->y;

    this->rectPlayer.w = this->width;
    this->rectPlayer.h = this->height;
    this->initRays();
}

void Player::move(char c)
{

    int direction = getAbsoluteDirection(this->angleVision);

    switch (direction)
    {
    case 1:
        // haut
        switch (c)
        {
        case 'z':
            // this->moveUp();

            this->avancer();
            break;
        case 'q':
            this->moveLeft();
            break;
        case 's':
            // this->moveDown();
            this->reculer();
            break;
        case 'd':
            this->moveRight();
            break;
        default:
            break;
        }
        break;

    case 2:
        // droite
        switch (c)
        {
        case 'z':
            // this->moveRight();

            this->avancer();
            break;
        case 'q':
            this->moveUp();

            break;
        case 's':
            // this->moveLeft();
            this->reculer();
            break;
        case 'd':
            this->moveDown();
            // this->x-=std::cos(this->angleVision)*this->velocity;
            // this->y-=std::sin(this->angleVision)*this->velocity;
            break;
        default:
            break;
        }
        break;

    case 3:
        // bas
        switch (c)
        {
        case 'z':
            // this->moveDown();
            this->avancer();
            break;
        case 'q':
            this->moveRight();
            break;
        case 's':
            // this->moveUp();
            this->reculer();
            break;
        case 'd':
            this->moveLeft();
            break;
        default:
            break;
        }
        break;

    case 4:
        // gauche
        switch (c)
        {
        case 'z':
            this->avancer();
            break;
        case 'q':
            this->moveDown();

            break;
        case 's':
            this->reculer();
            break;
        case 'd':
            this->moveUp();

            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void Player::moveLeft()
{

    this->x -= this->velocity;
    this->rectPlayer.x = this->x;
};
void Player::moveRight()
{

    this->x += this->velocity;
    this->rectPlayer.x = this->x;
};
void Player::moveUp()
{

    this->y -= this->velocity;
    this->rectPlayer.y = this->y;
};
void Player::moveDown()
{

    this->y += this->velocity;
    this->rectPlayer.y = this->y;
};
void Player::drawPlayer()
{
    SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(this->renderer, this->getRect());
}
SDL_Point Player::getCenter()
{
    int centerX = this->x + this->width / 2;
    int centerY = this->y + this->height / 2;
    SDL_Point point;
    point.x = centerX;
    point.y = centerY;
    return point;
}
void Player::updateAngleVision(SDL_Renderer *renderer, int degres)
{

    this->angleVision = this->angleVision + degres * M_PI / 180;
    this->angleVision = fmod(this->angleVision + 2 * M_PI, 2 * M_PI);
    Ray r{0, 0, 0};
    r.setAngle(this->angleVision);
    // std::cout << this->angleVision << std::endl;
};
void Player::renderRay(Ray &r,int pos){
    float dist=r.getLength();
    int wallHeight=((CELL_SIZE*5)/dist)*250;
    SDL_Rect rect;
    //rect.x=10*pos+800-5;//tmp
    static int wallWidth=2;
    rect.x=wallWidth*pos;
    rect.y=HEIGHT/2-wallHeight/2;
    rect.w=wallWidth;
    rect.h=wallHeight;
    if(r.getVerticalCollide()==false){
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 0);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);

    }
    SDL_RenderFillRect(this->renderer,&rect);


}
void Player::drawDirection()
{

    static int radius = 200;
    SDL_Point center = this->getCenter();
    int x1 = static_cast<int>(center.x + radius * std::cos(this->angleVision));
    int y1 = static_cast<int>(center.y + radius * std::sin(this->angleVision));

    float res = std::fmod(this->angleVision, 360.0f);
    // getAbsoluteDirection(this->angleVision);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderDrawPoint(renderer, x1, y1);

    SDL_RenderDrawLine(this->renderer, x1, y1, center.x, center.y);

    // this->getRays();
}


bool outOfMapBounds(int x, int y, std::vector<std::vector<int>> &map)
{
    return x < 0 || x >= map[0].size() || y < 0 || y >= map.size();
}

void Player::initRays()
{
    for (int i = 0; i < NB_RAYS; i++)
    {
        lstRays.push_back(Ray{i, i, 0});
    }
}
Ray Player::getHcollision(float angle, std::vector<std::vector<int>> &map)
{
    float pX = this->getCenter().x;
    float pY = this->getCenter().y;
    
    int up = abs(floor(fmod((angle / M_PI) , 2)));
    int firstY = up
                     ? floor(pY / CELL_SIZE) * CELL_SIZE
                     : floor(pY / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
    int firstX = pX + (firstY - pY) / tan(angle);

    float yA = up ? -CELL_SIZE : CELL_SIZE;
    float xA = yA / tan(angle);

    int wall;
    int nextX = firstX;
    int nextY = firstY;
    wall=0;
    while (wall!=1)
    {
        int cellX = floor(nextX / CELL_SIZE);
        int cellY = up
                        ? floor(nextY / CELL_SIZE) - 1
                        : floor(nextY / CELL_SIZE);

        if (outOfMapBounds(cellX, cellY,map))
        {
            break;
        }

        wall = map[cellY][cellX];
        if (!wall)
        {
            nextX += xA;
            nextY += yA;
        }
    }

    Ray r{nextX,nextY,distance(pX,pY,nextX+0.5,nextY+0.5)};
    r.setVerticalCollide(false);
    return r;
}

Ray Player::getVcollision(float angle, std::vector<std::vector<int>> &map)
{
    float pX = this->getCenter().x;
    float pY = this->getCenter().y;
    float right = abs(floor(fmod(((angle - M_PI / 2) / M_PI), 2)));
    float firstX = right
                       ? floor(pX / CELL_SIZE) * CELL_SIZE + CELL_SIZE
                       : floor(pX / CELL_SIZE) * CELL_SIZE;

    float firstY = pY + (firstX - pX) * tan(angle);

    float xA = right ? CELL_SIZE : -CELL_SIZE;
    float yA = xA * tan(angle);

    int wall;
    int nextX = firstX;
    int nextY = firstY;
    wall=0;
    while (wall != 1)
    {

        int cellX = right
                        ? floor(nextX / CELL_SIZE)
                        : floor(nextX / CELL_SIZE) - 1;
        int cellY = floor(nextY / CELL_SIZE);

        if (outOfMapBounds(cellX, cellY, map))
        {
            break;
        }
        wall = map[cellY][cellX];
        if (wall != 1)
        {
            nextX += xA;
            nextY += yA;
        }
    };

    // r.setX(nextX);
    // r.setY(nextY);
    // r.setLength(distance(pX,pY,nextX,nextY));
    Ray r{nextX,nextY,distance(pX,pY,nextX+0.5,nextY+0.5)};
    r.setVerticalCollide(true);
    return r;

}

std::vector<Ray> Player::getRays(std::vector<std::vector<int>> map)
{
    float initialAngle = this->angleVision - FOV / 2;
    double angleStep = FOV / NB_RAYS;
    float angle;
    int x1, y1;
    SDL_Point center = this->getCenter();


    for (int i = 0; i < this->lstRays.size(); i++)
    {
        angle = this->angleVision - (FOV / 2) + angleStep * i;

        Ray r = this->castRay(angle,map);
        renderRay(r,i);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);// pr debug
        SDL_RenderDrawLine(this->renderer, r.getX(), r.getY(), center.x, center.y);
    }
    return lstRays;
}
Coord Player::computeXYRay(Ray &r, std::vector<std::vector<int>> map)
{
    float angle = r.getAngle();
    int posX = floor(this->x / CELL_SIZE);
    int posY = floor(this->y / CELL_SIZE);

    float startX = this->getCenter().x;
    float startY = this->getCenter().y;
    float x;
    float y;
    float tmp;
    float baseLength;
    float opposeLength;
    Coord nextCase;
    int wall;
    if (angle < (M_PI / 2) && angle > 0)
    {
        // std::cout<<"bas droite"<<std::endl;

        x = (1 + posX) * CELL_SIZE;
        y = startY;
        baseLength = distance(startX, startY, x, y);
        opposeLength = tan(angle) * baseLength;
        y += opposeLength;
        r.setX(x);
        r.setY(y);
        r.setBaseLength(baseLength);
        nextCase = getNextCase(r);
        wall = map[nextCase.x][nextCase.y];
        while (wall != 1)
        {
            baseLength += CELL_SIZE;
            opposeLength = getNewOpposeLength(r.getBaseLength(), opposeLength, baseLength);
            y = startY + opposeLength;
            x += CELL_SIZE;

            r.setX(x);
            r.setY(y);
            r.setBaseLength(baseLength);

            nextCase = getNextCase(r);
            wall = map[nextCase.x][nextCase.y];
            std::cout << nextCase.y << " " << nextCase.x << " " << map[nextCase.y][nextCase.x] << std::endl;
        }
    }
    else if (angle >= (M_PI / 2) && angle < M_PI)
    {
        // std::cout<<"bas gauche"<<std::endl;
        x = posX * CELL_SIZE;
        y = startY;
        baseLength = distance(startX, startY, x, y);
        opposeLength = tan(M_PI - angle) * baseLength;
        y += opposeLength;
        r.setX(x);
        r.setY(y);
        r.setBaseLength(baseLength);
    }
    else if (angle >= M_PI && angle < M_PI + (M_PI / 2))
    {
        // std::cout<<"haut gauche"<<std::endl;
        x = posX * CELL_SIZE;
        y = startY;
        baseLength = distance(startX, startY, x, y);
        opposeLength = tan(angle - M_PI) * baseLength;
        y -= opposeLength;
        r.setX(x);
        r.setY(y);
        r.setBaseLength(baseLength);
    }
    else
    {
        x = (1 + posX) * CELL_SIZE;
        y = startY;
        baseLength = distance(startX, startY, x, y);

        opposeLength = tan(angle - ((M_PI + 2 * M_PI))) * baseLength;
        y += opposeLength;
        r.setX(x);
        r.setY(y);
        r.setBaseLength(baseLength);
    }

    return this->getNextCase(r);
}

SDL_Rect *Player::getRect()
{
    return &this->rectPlayer;
}
float getNewOpposeLength(float baseLength, float opposeLength, float newBaseLength)
{
    return newBaseLength * opposeLength / baseLength;
}
int getAbsoluteDirection(float angle)
{
    float res = angle * (180 / M_PI);

    res = fmod(res, 360.0f);
    if (res < 0)
    {
        res += 360;
    }

    if (res > 225 && res < 315)
    {
        // std::cout << "haut " << res << std::endl;
        return 1;
    }
    else if (res > 315 || res < 45)
    {
        // std::cout << "droite " << res << std::endl;
        return 2;
    }
    else if (res > 45 && res < 135)
    {
        // std::cout << "bas " << res << std::endl;
        return 3;
    }
    else
    {
        // std::cout << "gauche " << res << std::endl;
        return 4;
    }
    // std::cout<<res<<std::endl;
}

void Player::avancer()
{
    this->x += std::cos(this->angleVision) * this->velocity;
    this->y += std::sin(this->angleVision) * this->velocity;

    this->rectPlayer.x = this->x;
    this->rectPlayer.y = this->y;
}

void Player::reculer()
{
    this->x -= std::cos(this->angleVision) * this->velocity;
    this->y -= std::sin(this->angleVision) * this->velocity;

    this->rectPlayer.x = this->x;
    this->rectPlayer.y = this->y;
}

float radiansTodegree(float angle)
{
    float res = angle * (180 / M_PI);

    res = fmod(res, 360.0f);
    if (res < 0)
    {
        res += 360;
    }
    return res;
}
Ray Player::castRay(float angle,std::vector<std::vector<int>> &map){
    Ray r1=this->getVcollision(angle,map);
    Ray r2=this->getHcollision(angle,map);
    
    if(r1.getLength()>r2.getLength()){
        return r2;
    }
    return r1;
}
Coord Player::getNextCase(Ray &r)
{
    Coord c;
    int posX = floor(this->x / CELL_SIZE);
    int posY = floor(this->y / CELL_SIZE);

    int x = floor(r.getX() / CELL_SIZE);
    int y = floor(r.getY() / CELL_SIZE);
    float angle = r.getAngle();

    if (angle > M_PI / 2 && angle < (2 * M_PI) - (M_PI / 2))
    {
        // gauche
        c.x = x - 1;
        c.y = y;
    }
    else
    {
        c.x = x;
        c.y = y;
    }

    return c;
}
float distance(float x1, float y1, float x2, float y2)
{
    float deltaX = x2 - x1;
    float deltaY = y2 - y1;

    float res = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    return res;
}