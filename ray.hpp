#ifndef __RAY__
#define __RAY__




class Ray{
    private:
    int x;
    int y;
    float length;
    float angle;
    float baseLength;

    public:
    Ray(int x,int y, float length);
    int getX();
    int getY();
    float getAngle();
    float getLength();
    float getBaseLength();

    void setX(int x);
    void setY(int y);
    void setAngle(float angle);
    void setBaseLength(float baseLength);
};


#endif