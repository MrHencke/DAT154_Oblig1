#include "Road.h"

void BottomRoad::autoPosition(RECT screen) {
    west_pos = screen.right / 2 - h_road_width;
    east_pos = screen.right / 2 + h_road_width;
    north_pos = screen.bottom / 2 + h_road_width;
    south_pos = screen.bottom;
    Road::autoPosition(screen);
};
/*
void BottomRoad::updateCars() {
    int lastCarYPos = north_pos/2;
    bool hasCarInFront = FALSE;
    for (std::list<Car*>::iterator it = inboundCars.begin(); it != inboundCars.end(); it++) {
        if ((*it)->getYPos() +car_size <= north_pos) {
            transferList.emplace_back(*it);
            inboundCars.remove(*it);
            break;
        }
        hasCarInFront = it != inboundCars.begin();
        int carYPos = (*it)->getYPos();
        if (carYPos < north_pos + 2 * car_size && carYPos > north_pos && (*it)->getDestination() != direction) {
            if (trafficLight->isGreen()) {
                (*it)->updatePosition();
            }
        }
        else if (hasCarInFront) {
            if (!(carYPos < lastCarYPos + (car_size + car_spacing) && carYPos > lastCarYPos) ) {
                (*it)->updatePosition();
            }
        }
        else {
            (*it)->updatePosition();
        }
        lastCarYPos = (*it)->getYPos();
    }
    Road::updateCars();
}*/

void BottomRoad::setLanes(RECT screen) {
    for (int i = 0; i < inboundLanes.size();i++) {
        inboundLanes[i] = new VerticalLane(i, east_pos - (i+1) * lane_width + (lane_width / 2), south_pos, north_pos);
    }    
    for (int i = 0; i < outboundLanes.size();i++) {
        outboundLanes[i] = new OutboundLane(i);
    }
}