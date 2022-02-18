#include "Road.h"

void RightRoad::autoPosition(RECT screen) {
    west_pos = screen.right / 2 + h_road_width;
    north_pos = screen.bottom / 2 - h_road_width;
    south_pos = screen.bottom / 2 + h_road_width;
    east_pos = screen.right;
    Road::autoPosition(screen);
};

void RightRoad::updateCars() {
    int lastCarXPos = west_pos / 2;
    bool hasCarInFront = FALSE;
    for (std::list<Car*>::iterator it = inboundCars.begin(); it != inboundCars.end(); it++) {
        if ((*it)->getXPos() + car_size <= west_pos )  {
            transferList.emplace_back(*it);
            inboundCars.remove(*it);
            break;
        }
        hasCarInFront = it != inboundCars.begin();
        int carXPos = (*it)->getXPos();
        if (carXPos < west_pos + 2 * car_size && carXPos > west_pos && (*it)->getDestination() != direction) {
            if (trafficLight->isGreen()) {
                (*it)->updatePosition();
            }
        }
        else if (hasCarInFront) {
            if (!(carXPos < lastCarXPos + (car_size + car_spacing) && carXPos > lastCarXPos)) {
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

void RightRoad::setLanes(RECT screen) {
    int i = 0;
    for (auto& lane : lanes) {
        lane = std::make_pair(east_pos, i * lane_width + (lane_width / 2) + north_pos);
        i++;
    }
}