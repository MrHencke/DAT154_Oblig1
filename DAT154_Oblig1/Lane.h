#pragma once
#ifndef LANE_H
#define LANE_H
#include "Config.h"
#include "Car.h"
#include "list"

class Lane {
protected:
	int id;
	std::list<Car*> cars;

public: 
	Lane();
	void draw(HDC hdc);
	void addCar(Car* car);
};

class OutboundLane : public Lane {

public:
	OutboundLane(int id);
	void updateCars();
};

class InboundLane : public Lane{
protected:
	int x_pos;
	int y_pos;
	int inner;
	std::list<Car*> transferList;

public:
	InboundLane(int id, int x, int y, int inner);
	void addNewCar(Direction direction);
	void clearTransferList();
	std::list<Car*> getTransferList();
	virtual void updateCars(bool greenLight) = 0;
};

class HorizontalLane : public InboundLane {
public:
	HorizontalLane(int id, int x, int y, int inner) : InboundLane(id, x, y, inner) {};
	void updateCars(bool greenLight) override;
};

class VerticalLane : public InboundLane {
public:
	VerticalLane(int id, int x, int y, int inner) : InboundLane( id, x, y, inner){};
	void updateCars(bool greenLight) override;
};
#endif

