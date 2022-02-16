#include "framework.h"
#include "Road.h"
#include "Colors.h"
#include "Config.h"
#include "TrafficLight.h"
#include "Lane.h"


Road::Road()
{
    this->cars = std::list<Car*>();
    this->transferList = std::list<Car*>();
    this->west_pos = 0;
    this->north_pos = 0;
    this->east_pos = 0;
    this->south_pos = 0;
}

void Road :: draw(HDC hdc) {
    trafficLight->draw(hdc);
}

void Road::autoPosition(RECT screen) {
    trafficLight->autoPosition(screen);
}

TrafficLight* Road::getTrafficLight()
{
    return trafficLight;
}


void Road::addCar(Car*car) {
    cars.emplace_back(car);
}

std::list<Car*> Road::getTransferList() {
    return transferList;
}

void Road::clearTransferList() {
    transferList = {};
}


void Road::moveToTransferList() {
    //Fix later
    //transferList.emplace_front(*it);
    //cars.remove(*it);

}              