#include "framework.h"
#include "Road.h"
#include "Colors.h"
#include "Config.h"
#include "TrafficLight.h"
#include "Lane.h"

Road::Road(Direction direction){
    this->west_pos = 0;
    this->north_pos = 0;
    this->east_pos = 0;
    this->south_pos = 0;
    this->direction = direction;
    this->trafficLight = new TrafficLight(direction);
    this->inboundCars = std::list<Car*>();
    this->outboundCars = std::list<Car*>();
    this->transferList = std::list<Car*>();
    this->lanes = std::array<std::pair<int, int>, road_lanes/2>();
}

void Road::draw(HDC hdc) {
        HBRUSH brush = CreateSolidBrush(col_dark_gray);
        HGDIOBJ hOrg = SelectObject(hdc, brush);

        //Draw initial roads
        Rectangle(hdc, west_pos, north_pos, east_pos, south_pos);
        SelectObject(hdc, hOrg);
        DeleteObject(brush);

        for (const auto& car : inboundCars) {
            car->draw(hdc);
        }
        for (const auto& car : outboundCars) {
            car->draw(hdc);
        }
    
    trafficLight->draw(hdc);
}

void Road::autoPosition(RECT screen) {
    trafficLight->autoPosition(screen);
}

TrafficLight* Road::getTrafficLight(){
    return trafficLight;
}


void Road::addOutboundCar(Car*car) {
    outboundCars.emplace_back(car);
}

void Road::addNewInboundCar() {
    std::pair<int, int> lane = getRandomLane();
    inboundCars.emplace_back(new Car(lane.first, lane.second, direction));
}

std::list<Car*> Road::getTransferList() {
    return transferList;
}

void Road::clearTransferList() {
    transferList = {};
}

std::pair<int, int> Road::getRandomLane() {
    return lanes[rand() % lanes.size()];
}

void Road::updateCars() {
    for (auto* car : outboundCars) {
        car->updatePosition();
    }
}