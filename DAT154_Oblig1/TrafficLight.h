#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
#include "framework.h"

//Constants
const int width = 120;
const int height = width * 3;
const int margin = width / 10;

class TrafficLight {
	
    private:
        int x_pos;
        int y_pos;
        int state;
    public:
        TrafficLight();
        TrafficLight(int x_pos, int y_pos);
        void draw(HDC hdc);
        void setState(int x);
        void incState();
        void decState();
        void refresh(HWND hWnd);
        void setCoords(int x, int y);
        void setX(int x);
        void setY(int y);
};
#endif