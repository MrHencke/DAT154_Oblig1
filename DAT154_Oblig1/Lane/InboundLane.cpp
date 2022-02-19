#include "Lane.h"


InboundLane::InboundLane(int id, int x, int y, int inner) : Lane() {
	this->id = id;
	this->x_pos = x;
	this->y_pos = y;
	this->inner = inner;
	this->transferList = std::list<Car*>();
}

std::list<Car*> InboundLane::getTransferList() {
	return transferList;
}

void InboundLane::clearTransferList() {
	transferList = {};
}

void InboundLane::addNewCar(Direction direction) {
	cars.emplace_back(new Car(x_pos, y_pos, direction));
}