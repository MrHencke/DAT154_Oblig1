#include "Road.h"

void LeftRoad::autoPosition(RECT screen) {
        north_pos = screen.bottom / 2 - h_road_width;
        east_pos = screen.right / 2 - h_road_width;
        south_pos = screen.bottom / 2 + h_road_width;
        Road::autoPosition(screen);
};

void LeftRoad::setLanes(RECT screen) {
    for (int i = 0; i < inboundLanes.size(); i++) {
        inboundLanes[i] = new LeftLane(i, west_pos, south_pos - (i+1) * lane_width + (lane_width / 2), east_pos);
    }
    for (int i = 0; i < outboundLanes.size(); i++) {
        outboundLanes[i] = new OutboundLane(i);
    }


}