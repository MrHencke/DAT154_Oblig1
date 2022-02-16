#include "TrafficController.h"
#include "Intersection.h"
#include "Road.h"
#include "TrafficLight.h"


TrafficController::TrafficController() {
	this -> intersection = Intersection();
	this -> roads = std::vector<Road*>({ new Road(Direction::n), new Road(Direction::w), new Road(Direction::s), new Road(Direction::e) });
	this -> trafficLights = std::vector<TrafficLight*>({ new TrafficLight(Direction::n),  new TrafficLight(Direction::w),  new TrafficLight(Direction::s),  new TrafficLight(Direction::e) });
}


void TrafficController::drawAll(HDC hdc) {
	for (Road * road : roads) {
		road->draw(hdc);
	}
	intersection.draw(hdc);
	for (TrafficLight * tl : trafficLights) {
		tl->draw(hdc);
	}
}

void TrafficController::positionAll(RECT screen) {
	intersection.autoPosition(screen);
	for (auto road : roads) {
		road->autoPosition(screen);
	}
	for (auto tl : trafficLights) {
		tl->autoPosition(screen);
	}
}

void TrafficController::refreshAllTrafficLights(HWND hWnd) {
	for (auto tl : trafficLights) {
		tl->refresh(hWnd);
	}
}

int TrafficController::incrementAllTrafficLights() {
	if (abs(trafficLights[0]->getState() - trafficLights[1]->getState()) == 2) {
		for (auto tl : trafficLights) {
			tl->incState();
		}
		if (trafficLights[0]->getState() == 1 || trafficLights[0]->getState() == 3) {
			return 1;// SetTimer(hWnd, 0, yellow_interval, NULL);
		}
		else {
			return 0; //SetTimer(hWnd, 0, red_green_interval, NULL);

		}
	}
	else {
		trafficLights[0]->incState();
		trafficLights[2]->incState();
		return 1;//SetTimer(hWnd, 0, yellow_interval, NULL);
	}
}

void TrafficController::addCarToRoad(Direction start, Direction destination) {
	roads[start]->newCar(destination);
}

void TrafficController::refreshRoad(HWND hWnd, Direction direction) {
	roads[direction]->refresh(hWnd);
}

void TrafficController::refreshAllRoads(HWND hWnd) {
	for (auto road : roads) {
		road->refresh(hWnd);
	}
	intersection.refresh(hWnd);
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
			roads[destination]->addCar(car);
		}
		intersection.clearTransferList();
	}
}