#ifndef __RAY__
#define __RAY__




class Ray{
    private:
    int x;
    int y;
    float length;
    float angle;
    float baseLength;
    bool verticalCollide;

    public:
    Ray(int x,int y, float length);
    int getX();
    int getY();
    float getAngle();
    float getLength();
    float getBaseLength();
    bool getVerticalCollide();
    

    void setX(int x);
    void setY(int y);
    void setAngle(float angle);
    void setBaseLength(float baseLength);
    void setLength(float l);
    void setVerticalCollide(bool x);
};


#endif