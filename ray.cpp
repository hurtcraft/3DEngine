#include <iostream>
#include "ray.hpp"

Ray::Ray(int x, int y, float length) : x(x), y(y), length(length)
{
}
int Ray::getX()
{
    return this->x;
}
int Ray::getY()
{
    return this->y;
}
float Ray::getLength()
{
    return this->length;
}
float Ray::getAngle() {
    return this->angle;
}
float Ray::getBaseLength(){
    return this->baseLength;
}
bool Ray::getVerticalCollide(){
    return this->verticalCollide;
}


void Ray::setX(int x){
    this->x=x;
};
void Ray::setY(int y){
    this->y=y;
};
void Ray::setAngle(float angle){
    this->angle=angle;
}
void Ray::setBaseLength(float baseLength){
    this->baseLength=baseLength;
}
void Ray::setLength(float l){
    this->length=l;
}
void Ray::setVerticalCollide(bool x){
    this->verticalCollide=x;
}