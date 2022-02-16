#pragma once
#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H
#include "Intersection.h"
#include "TrafficLight.h"

class TrafficController {
private:
	Intersection intersection;
	std::vector <Road*> roads; 
	std::vector <TrafficLight*> trafficLights;
public:
	TrafficController();
	void drawAll(HDC hdc);
	void positionAll(RECT screen);
	int incrementAllTrafficLights();
	void refreshAllTrafficLights(HWND hWnd);
	void addCarToRoad(Direction start, Direction destination);
	void refreshRoad(HWND hWnd,Direction direction);
	void refreshAllRoads(HWND hWnd);
	void updateAllCars();

};

#endif 
