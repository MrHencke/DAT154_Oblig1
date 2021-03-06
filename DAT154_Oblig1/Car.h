#pragma once
#ifndef CAR_H
#define CAR_H
#include "framework.h"
#include "Config.h"

const int car_speed = 3;
const int car_size = 20;
const int car_spacing = 30;

class Car {
	private:
		int x_pos;
		int y_pos;
		Direction currentDirection;
		Direction start;
		Direction destination;
		int size;
		int speed;
		COLORREF color;

	public:
		Car(int x_pos, int y_pos, Direction start);
		int getYPos();
		int getXPos();
		int getSize();
		void draw(HDC hdc);
		void updatePosition();
		Direction getDestination();
};


#endif