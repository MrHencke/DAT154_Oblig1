#include "Lane.h"

Lane::Lane() {
	this->id = 0;
	this->cars = std::list<Car*>();
}

void Lane::draw(HDC hdc){
	for (auto* car : cars) {
		car->draw(hdc);
	}
}


void Lane::addCar(Car * car) {
	cars.emplace_back(car);
}

