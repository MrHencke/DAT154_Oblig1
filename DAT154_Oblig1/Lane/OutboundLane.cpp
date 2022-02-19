#include "Lane.h"

OutboundLane::OutboundLane(int outer) : Lane() {
	this->outer = outer;
};
void OutboundLane::updateCars() {
	for (std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++) {
		int XPos = (*it)->getXPos();
		int YPos = (*it)->getYPos();
		int CarSize = (*it)->getSize();
		Direction direction = (*it)->getDestination();
		if (XPos > outer && direction == e || XPos < outer && direction == w || YPos < outer && direction == n || YPos > outer && direction == s) {
			Car* ref = (*it);
			cars.remove(*it);
			delete(ref);
			break;
		}
		else {
			(*it)->updatePosition();
		}
	}
}