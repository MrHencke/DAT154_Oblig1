#include "Road.h"
#include "../framework.h"
#include "../Colors.h"
#include "../TrafficLight.h"

Road::Road(Direction direction){
    this->west_pos = 0;
    this->north_pos = 0;
    this->east_pos = 0;
    this->south_pos = 0;
    this->direction = direction;
    this->trafficLight = new TrafficLight(direction);
    this->inboundLanes = std::array<InboundLane*, road_lanes/2>();
    this->outboundLanes = std::array<OutboundLane*, road_lanes / 2>();
    this->transferList = std::list<Car*>();
}

void Road::draw(HDC hdc) {
        HBRUSH brush = CreateSolidBrush(col_dark_gray);
        HGDIOBJ hOrg = SelectObject(hdc, brush);

        //Draw initial roads
        Rectangle(hdc, west_pos, north_pos, east_pos, south_pos);
        SelectObject(hdc, hOrg);
        DeleteObject(brush);

        for (const auto& lane : inboundLanes) {
            lane->draw(hdc);
        }
        for (const auto& lane : outboundLanes) {
            lane->draw(hdc);
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
    outboundLanes[0]->addCar(car); //TODO Dynamically set to correct lane
}

void Road::addNewInboundCar() {
    InboundLane* lane = getRandomInboundLane();
    lane->addNewCar(direction);
}

std::list<Car*> Road::getTransferList() {
    return transferList;
}

void Road::clearTransferList() {
    transferList = {};
}

InboundLane* Road::getRandomInboundLane() {
    return inboundLanes[rand() % inboundLanes.size()];
}

void Road::updateCars() {
    for (auto* lane : inboundLanes) {
        lane->updateCars(trafficLight->isGreen());
        if (lane->getTransferList().size() > 0) {
            transferList.splice(transferList.begin(), lane->getTransferList());
            lane->clearTransferList();
        }
    }
    for (auto* lane : outboundLanes) {
        lane->updateCars();
    }
}