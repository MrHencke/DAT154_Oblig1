#pragma once
#ifndef LANE_H
#define LANE_H
#include "../Config.h"
#include "../Car.h"
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
private:
	int outer;

public:
	OutboundLane(int outer);
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
};

class VerticalLane : public InboundLane {
public:
	VerticalLane(int id, int x, int y, int inner) : InboundLane( id, x, y, inner){};
};

class LeftLane : public HorizontalLane {
public:
	LeftLane(int id, int x, int y, int inner) : HorizontalLane(id, x, y, inner) {};
	void updateCars(bool greenLight) override;
};

class RightLane : public HorizontalLane {
public:
	RightLane(int id, int x, int y, int inner) : HorizontalLane(id, x, y, inner) {};
	void updateCars(bool greenLight) override;
};

class TopLane : public VerticalLane {
public:
	TopLane(int id, int x, int y, int inner) : VerticalLane(id, x, y, inner) {};
	void updateCars(bool greenLight) override;
};

class BottomLane : public VerticalLane {
public:
	BottomLane(int id, int x, int y, int inner) : VerticalLane(id, x, y, inner) {};
	void updateCars(bool greenLight) override;
};
#endif

