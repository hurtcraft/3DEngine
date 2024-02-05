#ifndef __PLAYER__
#define __PLAYER__
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>
#include "ray.hpp"
#include <vector>
#include "coord.hpp"
class Player{
private : 
    SDL_Renderer *renderer;
    std::string nom;
    int hp;
    int width=10;
    int height=10;
    float x;
    float y;
    float dx;
    float dy;

    int velocity=2;

    //const int FOV=60;
    float angleVision=0;
    //std::unordered_map<char, std::function<void()>> mapMoves;
    
    SDL_Rect rectPlayer;
    std::vector<Ray> lstRays;
    
public :
    Player(SDL_Renderer *renderer,std::string nom,int hp,float x,float y);

    void move(char c);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void avancer();
    void reculer();
    void updateAngleVision(SDL_Renderer *renderer, int degres);
    
    void drawPlayer();
    void drawDirection();
    
    std::vector<Ray> getRays(std::vector<std::vector<int>>);
    Ray castRay(float angle,std::vector<std::vector<int>> &map);
    Ray getHcollision(float angle,std::vector<std::vector<int>> &map);
    Ray getVcollision(float angle,std::vector<std::vector<int>> &map);
    SDL_Point getCenter();
    SDL_Rect *getRect();

    Coord computeXYRay(Ray &r,std::vector<std::vector<int>> map);
    Coord getNextCase(Ray &r);
    void initRays();
    void renderRay(Ray &r,int pos);
};

int getAbsoluteDirection(float angle);//1:haut 2:droite 3:bas 4:gauche
int getRelativeDirection(float angle); // 0 pour gauche 1 pour droite
float getNewOpposeLength(float baseLength,float opposeLength,float newBaseLength);
float radiansTodegree(float angle);


float distance(float x1, float y1, float x2, float y2);
#endif