#pragma once
#ifndef ROAD_H
#define ROAD_H
#include "framework.h"
#include "TrafficLight.h"
#include "Config.h"
#include "Lane.h"
#include "list"

class Road {

private:
    Direction direction;
    std::list<int> lanes;
    std::list<Car*> transferList;
    std::list<Car*> cars;
    int west_pos;
    int north_pos;
    int south_pos;
    int east_pos;
    int start;
    int end;
    void moveToTransferList();
public:
    Road();
    Road(Direction direction);
    void draw(HDC hdc);
    void refresh(HWND hWnd);
    void addCar(Car* car);
    void newCar(Direction destination);
    void updateCars();
    void autoPosition(RECT screen);
    std::list<Car*> getTransferList();
    void clearTransferList();
};
#endif