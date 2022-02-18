#include "TrafficController.h"
#include "Intersection.h"
#include "Road.h"
#include "TrafficLight.h"


TrafficController::TrafficController() {
	this -> intersection = Intersection();
	this -> roads = std::vector<Road*>({ new TopRoad(), new LeftRoad(), new BottomRoad(), new RightRoad() });
}


void TrafficController::drawAll(HDC hdc) {
	intersection.draw(hdc);
	for (Road * road : roads) {
		road->draw(hdc);
	}
}

void TrafficController::positionAll(RECT screen) {
	intersection.autoPosition(screen);
	for (auto road : roads) {
		road->autoPosition(screen);
		road->setLanes(screen);
	}
}


int TrafficController::incrementAllTrafficLights() {

	if (abs(roads[0]->getTrafficLight()->getState() - roads[1]->getTrafficLight()->getState()) == 2) {
		for (auto road : roads) {
			road->getTrafficLight()->incState();
		}
		if (roads[0]->getTrafficLight()->getState() == 1 || roads[0]->getTrafficLight()->getState() == 3) {
			return 1;// SetTimer(hWnd, 0, yellow_interval, NULL);
		}
		else {
			return 0; //SetTimer(hWnd, 0, red_green_interval, NULL);

		}
	}
	else {
		roads[0]->getTrafficLight()->incState();
		roads[2]->getTrafficLight()->incState();
		return 1;//SetTimer(hWnd, 0, yellow_interval, NULL);
	}
}

void TrafficController::addCarToRoad(Direction start, Direction destination) {
	roads[start]->addNewInboundCar();
}

void TrafficController::updateAllCars() {
	for (auto road : roads) {
		road->updateCars();
		if (road->getTransferList().size() > 0) {
			intersection.addCars((road->getTransferList()));
			road->clearTransferList();
		}
	}
	intersection.updateCars();
	if (intersection.getTransferList().size() > 0) {
		auto cars = intersection.getTransferList();
		for (auto car : cars) {
			int destination = car->getDestination();
			roads[destination]->addOutboundCar(car);
		}
		intersection.clearTransferList();
	}
}