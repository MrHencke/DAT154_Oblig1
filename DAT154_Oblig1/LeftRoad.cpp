#include "Road.h"

void LeftRoad::autoPosition(RECT screen) {
        north_pos = screen.bottom / 2 - h_road_width;
        east_pos = screen.right / 2 - h_road_width;
        south_pos = screen.bottom / 2 + h_road_width;
        Road::autoPosition(screen);
};
/*
void LeftRoad::updateCars() {
    int lastCarXPos = east_pos * 2;
    bool hasCarInFront = FALSE;
    for (std::list<Car*>::iterator it = inboundCars.begin(); it != inboundCars.end(); it++) {
        if ((*it)->getXPos() - car_size >= east_pos) {
            transferList.emplace_back(*it);
            inboundCars.remove(*it);
            break;
        }
        hasCarInFront = it != inboundCars.begin();
        int carXPos = (*it)->getXPos();
        if (carXPos > east_pos - 2 * car_size && carXPos < east_pos && (*it)->getDestination() != direction) {
            if (trafficLight->isGreen()) {
                (*it)->updatePosition();
            }
        }
        else if (hasCarInFront) {
            if (!(carXPos > lastCarXPos - (car_size + car_spacing) && carXPos < lastCarXPos)) {
                (*it)->updatePosition();
            }
        }
        else {
            (*it)->updatePosition();
        }
        lastCarXPos = (*it)->getXPos();
    }
    Road::updateCars();

}
*/

void LeftRoad::setLanes(RECT screen) {
    for (int i = 0; i < inboundLanes.size(); i++) {
        inboundLanes[i] = new HorizontalLane(i, west_pos, south_pos - (i+1) * lane_width + (lane_width / 2), east_pos);
    }
    for (int i = 0; i < outboundLanes.size(); i++) {
        outboundLanes[i] = new OutboundLane(i);
    }


}