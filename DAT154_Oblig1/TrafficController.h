#pragma once
#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H
#include "Intersection.h"

class TrafficController {
private:
	Intersection intersection;
	std::vector <Road*> roads; 
public:
	TrafficController();
	void drawAll(HDC hdc);
	void positionAll(RECT screen);
	int incrementAllTrafficLights();
	void addCarToRoad(Direction start, Direction destination);
	void refreshRoad(HWND hWnd,Direction direction);
	void refreshAllRoads(HWND hWnd);
	void updateAllCars();
};

#endif 
