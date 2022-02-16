#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
#include "framework.h"
#include "Config.h"


//Constants
const int tl_width = 120;
const int tl_height = tl_width * 3;
const int tl_margin = tl_width / 10;

class TrafficLight {
	
    private:
        Direction direction;
        int west_pos;
        int north_pos;
        int east_pos;
        int south_pos;
        int state;
    public:
        TrafficLight();
        TrafficLight(Direction direction);
        void draw(HDC hdc);
        void setState(int x);
        int getState();
        bool isGreen();
        void incStateRefresh(HWND hWnd);
        void incState();
        void decState();
        void refresh(HWND hWnd);
        void autoPosition(RECT screen);
};
#endif