#pragma once
#ifndef CAR_H
#define CAR_H
#include "framework.h"
#include "Config.h"

enum class carState {
	driving = 0,
	stopped,
	transferring
};

const int car_speed = 1;
const int car_size = 20;
const int car_spacing = 15;

class Car {
	private:
		int x_pos;
		int y_pos;
		Direction currentDirection;
		Direction start;
		Direction destination;
		int size;
		float speed;

	public:
		Car();
		Car(int x_pos, int y_pos, Direction start, Direction destination, int size, int speed);
		int getYPos();
		int getXPos();
		int getSize();
		void draw(HDC hdc);
		void updatePosition();
		Direction getDestination();
};


#endif