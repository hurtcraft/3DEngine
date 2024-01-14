
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
    // computeXYRay(r);
};

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

void Player::castRay(float angle, std::vector<std::vector<int>> &map)
{
    // this->getVcollision(angle, map, DROITE);
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
void Player::getHcollision(Ray &r, std::vector<std::vector<int>> &map, int direction)
{

    Coord c = this->computeXYRay(r, this->getCenter().x, this->getCenter().y);

    int wall = map[c.x][c.y];
    float x = r.getX();
    float y = r.getY();
    c = this->computeXYRay(r, x, y);
    wall = map[c.x][c.y];
    std::cout << c.x << " " << c.y << " " << wall << std::endl;
}

void Player::getVcollision(Ray &r, std::vector<std::vector<int>> &map, int direction)
{
}

std::vector<Ray> Player::getRays(std::vector<std::vector<int>> map)
{
    float initialAngle = this->angleVision - FOV / 2;
    float angleStep = FOV / NB_RAYS;
    float angle;
    int x1, y1;
    SDL_Point center = this->getCenter();
    static int radius = 200;

    int firstX;
    static int half_NB_RAYS = NB_RAYS / 2;
    Ray *r;
    int absDirection;
    for (int i = 0; i < this->lstRays.size(); i++)
    {
        angle = this->angleVision - (FOV / 2) + angleStep * i;
        x1 = static_cast<int>(center.x + radius * std::cos(angle));
        y1 = static_cast<int>(center.y + radius * std::sin(angle));

        r = &lstRays[i];
        r->setAngle(this->angleVision);

        getHcollision(*r, map, 1);
        // std::cout<<c.x<<" "<<c.y<<std::endl;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        SDL_RenderDrawLine(this->renderer, r->getX(), r->getY(), center.x, center.y);
    }
    return lstRays;
}

SDL_Rect *Player::getRect()
{
    return &this->rectPlayer;
}

// int getRelativeDirection(float angle)
// {

//     int absDir = getAbsoluteDirection(angle);
//     angle = radiansTodegree(angle);
//     switch (absDir)
//     {
//     case 1:
//         if (angle < 270.0f)
//         {
//             return GAUCHE;
//         }
//         return DROITE;
//         break;
//     case 2:
//         if ((angle < 360.0f && angle > 315.0f))
//         {
//             return GAUCHE;
//         }
//         return DROITE;
//         break;
//     case 3:
//         if (angle < 90.0f)
//         {
//             return GAUCHE;
//         }
//         return DROITE;
//         break;
//     case 4:
//         if (angle < 180.0f)
//         {
//             return GAUCHE;
//         }
//         return DROITE;
//         break;

//     default:
//         break;
//     }
// }
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
Coord Player::computeXYRay(Ray &r, float startX, float startY)
{
    float angle = r.getAngle();
    int posX = floor(this->x / CELL_SIZE);
    int posY = floor(this->y / CELL_SIZE);

    float x;
    float y;
    float tmp;
    float baseLength;
    float opposeLength;
    Coord nextCase;
    if (angle < (M_PI / 2) && angle > 0)
    {
        // std::cout<<"bas droite"<<std::endl;

        x = (1 + posX) * CELL_SIZE;
        y = startY;
        baseLength = distance(startX, startY, x, y)+CELL_SIZE;
        SDL_RenderDrawLine(this->renderer,startX,startY,x+CELL_SIZE,y);
        opposeLength = tan(angle) * baseLength;
        y += opposeLength;
    }
    else if (angle >= (M_PI / 2) && angle < M_PI)
    {
        // std::cout<<"bas gauche"<<std::endl;
        x = posX * CELL_SIZE;
        y = startY;
        baseLength = distance(startX, startY, x, y);
        opposeLength = tan(M_PI - angle) * baseLength;
        y += opposeLength;
    }
    else if (angle >= M_PI && angle < M_PI + (M_PI / 2))
    {
        // std::cout<<"haut gauche"<<std::endl;
        x = posX * CELL_SIZE;
        y = startY;
        baseLength = distance(startX, startY, x, y);
        opposeLength = tan(angle - M_PI) * baseLength;
        y -= opposeLength;
    }
    else
    {
        x = (1 + posX) * CELL_SIZE;
        y = startY;
        baseLength = distance(startX, startY, x, y);

        opposeLength = tan(angle - ((M_PI + 2 * M_PI))) * baseLength;
        y += opposeLength;
    }
    r.setX(x);
    r.setY(y);
    r.setBaseLength(baseLength);
    return this->getNextCase(r);
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