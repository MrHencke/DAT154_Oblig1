#include "Road.h"

void TopRoad::autoPosition(RECT screen) {
        west_pos = screen.right / 2 - h_road_width;
        east_pos = screen.right / 2 + h_road_width;
        south_pos = screen.bottom / 2 - h_road_width;
        Road::autoPosition(screen);
};

/*
void TopRoad::updateCars() {
        int lastCarYPos = south_pos*2;
        bool hasCarInFront = FALSE;
    for (std::list<Car*>::iterator it = inboundCars.begin(); it != inboundCars.end(); it++) {
        if ((*it)->getYPos() - car_size >= south_pos) {
            transferList.emplace_back(*it);
            inboundCars.remove(*it);
            break;
        }
        hasCarInFront = it != inboundCars.begin();
        int carYPos = (*it)->getYPos();
        if (carYPos > south_pos -2*car_size && carYPos< south_pos && (*it)->getDestination() != direction) {
             if (trafficLight->isGreen()) {
                (*it)->updatePosition();
            }
         }
        else if (hasCarInFront) {
            if (!(carYPos > lastCarYPos - (car_size+car_spacing) && carYPos < lastCarYPos)) {
                (*it)->updatePosition();
            }
        }
        else {
            (*it)->updatePosition();
        }
        lastCarYPos = (*it)->getYPos();
    }
    Road::updateCars();
}
*/
void TopRoad::setLanes(RECT screen) {
        for (int i = 0; i < inboundLanes.size(); i++) {
            inboundLanes[i] = new VerticalLane(i, west_pos + i * lane_width + (lane_width / 2), north_pos, south_pos);
        }
        for (int i = 0; i < outboundLanes.size(); i++) {
            outboundLanes[i] = new OutboundLane(i);
        }
}