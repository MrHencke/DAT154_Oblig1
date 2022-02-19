#include "Lane.h"

OutboundLane::OutboundLane(int id) : Lane() {
	this->id = id;
};

void OutboundLane::updateCars() {
	for (auto* car : cars) {
		car->updatePosition();
	}
}