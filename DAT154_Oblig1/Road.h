#pragma once
#ifndef ROAD_H
#define ROAD_H
#include "TrafficLight.h"
#include "Config.h"
#include "Lane.h"
#include "list"
#include "array"


class Road {
protected:
    int west_pos;
    int north_pos;
    int south_pos;
    int east_pos;
    Direction direction;
    TrafficLight * trafficLight;
    std::array<InboundLane*, road_lanes/2> inboundLanes;
    std::array<OutboundLane*, road_lanes / 2> outboundLanes;
    std::list<Car*> transferList;
public:
    Road(Direction direction);
    virtual void draw(HDC hdc);
    virtual void drawLaneDivider(HDC hdc) = 0;
    virtual void updateCars();
    virtual void autoPosition(RECT screen);
    virtual void setLanes(RECT screen) = 0;
    TrafficLight* getTrafficLight();
    void addOutboundCar(Car* car);
    void addNewInboundCar();
    std::list<Car*> getTransferList();
    void clearTransferList();
    InboundLane* getRandomInboundLane();
};

class HorizontalRoad : public Road
{
public:
    HorizontalRoad(Direction direction) : Road(direction) {};
    void drawLaneDivider(HDC hdc) override;
};

class VerticalRoad : public Road{
public:
    VerticalRoad(Direction direction) : Road(direction){};
    void drawLaneDivider(HDC hdc) override;

};

class LeftRoad : public HorizontalRoad{
public:
    LeftRoad() : HorizontalRoad(w){};
    void autoPosition(RECT screen) override;
    //void updateCars() override;
    void setLanes(RECT screen) override;
};

class RightRoad : public HorizontalRoad{
public:
    RightRoad() : HorizontalRoad(e){};
    void autoPosition(RECT screen) override;
    //void updateCars() override;
    void setLanes(RECT screen) override;
};

class TopRoad : public VerticalRoad{
public:
    TopRoad() : VerticalRoad(n){};
    void autoPosition(RECT screen) override;
    //void updateCars() override;
    void setLanes(RECT screen) override;
};

class BottomRoad : public VerticalRoad{
public:
    BottomRoad() : VerticalRoad(s) {};
    void autoPosition(RECT screen) override;
    //void updateCars() override;
    void setLanes(RECT screen) override;
};
#endif