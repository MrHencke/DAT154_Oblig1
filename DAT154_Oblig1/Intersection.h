#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "framework.h"
#include "Road.h"

class Intersection {

private:
    std::list<Car*> cars;
    std::list<Car*> transferList;
    int west_pos;
    int north_pos;
    int east_pos;
    int south_pos;
public:
    Intersection();
    void draw(HDC hdc);
    void refresh(HWND hWnd);
    void updateCars();
    std::list<Car*> getTransferList();
    void clearTransferList();
    void addCars(std::list<Car*> cars);
    void autoPosition(RECT screen);
};
#endif
