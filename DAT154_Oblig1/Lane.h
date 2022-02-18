#pragma once

#ifndef LANE_H
#define LANE_H
#include "Config.h"
#include "Car.h"
#include "list"

class Lane
{
private:
	int x_pos;
	int y_pos;
	bool inbound;
	std::list<Car*> cars;

public:
	Lane();
	Lane(int x, int y, bool inbound);
	int getXPos();
	void setXPos(int x);
	int getYPos();
	void setYPos(int y);
};
#endif

