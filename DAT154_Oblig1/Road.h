#pragma once
#ifndef ROAD_H
#define ROAD_H
#include "framework.h"
#include "TrafficLight.h"
#include "Config.h"
#include "Lane.h"
#include "list"

class Road {

protected:
    Direction direction;
    std::list<int> lanes;
    TrafficLight * trafficLight;
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
    virtual void draw(HDC hdc) = 0;
    void addCar(Car* car);
    virtual void newCar(Direction destination) = 0;
    virtual void updateCars() = 0;
    virtual void autoPosition(RECT screen);
    TrafficLight* getTrafficLight();
    std::list<Car*> getTransferList();
    void clearTransferList();
};

class HorizontalRoad : public Road
{
public:
    HorizontalRoad();
    void draw(HDC hdc) override;
    void newCar(Direction destination) override;
};

class VerticalRoad : public Road
{
public:
    VerticalRoad();
    void draw(HDC hdc) override;
    void newCar(Direction destination) override;
};

class LeftRoad : public Road
{
public:
    LeftRoad();
    void draw(HDC hdc) override;
    void autoPosition(RECT screen) override;
    void newCar(Direction destination) override;
    void updateCars() override;
};

class RightRoad : public Road
{
public:
    RightRoad();
    void draw(HDC hdc) override;
    void autoPosition(RECT screen) override;
    void newCar(Direction destination) override;
    void updateCars() override;
};

class TopRoad : public Road
{
public:
    TopRoad();
    void draw(HDC hdc) override;
    void autoPosition(RECT screen) override;
    void newCar(Direction destination) override;
    void updateCars() override;
};

class BottomRoad : public Road
{
public:
    BottomRoad();
    void draw(HDC hdc) override;
    void autoPosition(RECT screen) override;
    void newCar(Direction destination) override;
    void updateCars() override;
};
#endif