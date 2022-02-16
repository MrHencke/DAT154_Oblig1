#pragma once

#ifndef LANE_H
#define LANE_H
#include "Config.h"
#include "Car.h"
#include <vector>

class Lane
{
private:
	int outerX;
	int outerY;
	int innerX;
	int innerY;


public:
	Lane();
	Lane(int outerX, int outerY);
	int getOuterX();
	void setOuterX(int x);
	int getOuterY();
	void setOuterY(int y);

};

#endif

