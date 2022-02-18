#include "Lane.h"

Lane::Lane() {
	this->id = 0;
	this->cars = std::list<Car*>();
}

OutboundLane::OutboundLane(int id) : Lane() {
	this->id = id;
};


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

void Lane::draw(HDC hdc){
	for (auto* car : cars) {
		car->draw(hdc);
	}
}

void InboundLane::addNewCar(Direction direction){
	cars.emplace_back(new Car(x_pos, y_pos, direction));
}

void Lane::addCar(Car * car) {
	cars.emplace_back(car);
}

void OutboundLane::updateCars() {
	for (auto* car : cars) {
		car->updatePosition();
	}
}

void HorizontalLane::updateCars(bool greenLight) {
	int lastCarXPos = 10000;
	bool hasCarInFront = FALSE;
	int XPos = 0;
	for (std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++) {
		XPos = (*it)->getXPos();
		if ((XPos + 2 * car_size >= inner && XPos <= inner) || (XPos - 2 * car_size <= inner && XPos >= inner)) {
			transferList.emplace_back(*it);
			cars.remove(*it);
			break;
		}
		hasCarInFront = it != cars.begin();
		if (XPos > inner - 2 * car_size && XPos < inner || XPos < inner + 2 * car_size && XPos > inner) {
			if (greenLight) {
				(*it)->updatePosition();
			}
		}
		else if (hasCarInFront) {
			if (!(XPos < lastCarXPos + (car_size + car_spacing) && XPos > lastCarXPos) || !(XPos > lastCarXPos - (car_size + car_spacing) && XPos < lastCarXPos)) {
				(*it)->updatePosition();
			}
		}
		else {
			(*it)->updatePosition();
		}
		lastCarXPos = (*it)->getXPos();
	}
}

void VerticalLane::updateCars(bool greenLight) {
	int lastCarYPos = 10000;
	bool hasCarInFront = FALSE;
	int YPos = 0;
	for (std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++) {
		YPos = (*it)->getYPos();
		if ((YPos > inner - 2 * car_size && YPos < inner) || (YPos - 2*car_size <= inner && YPos >= inner)) {
			transferList.emplace_back(*it);
			cars.remove(*it);
			break;
		}
		hasCarInFront = it != cars.begin();
		if (YPos > inner - 2 * car_size && YPos < inner || YPos < inner + 2 * car_size && YPos > inner) {
			if (greenLight) {
				(*it)->updatePosition();
			}
		}
		else if (hasCarInFront) {
			if (!(YPos > lastCarYPos - (car_size + car_spacing) && YPos < lastCarYPos) || !(YPos < lastCarYPos + (car_size + car_spacing) && YPos > lastCarYPos)) {
				(*it)->updatePosition();
			}
		}
		else {
			(*it)->updatePosition();
		}
		lastCarYPos = (*it)->getYPos();
		}
}
