#include "Road.h"

void RightRoad::autoPosition(RECT screen) {
    west_pos = screen.right / 2 + h_road_width;
    north_pos = screen.bottom / 2 - h_road_width;
    south_pos = screen.bottom / 2 + h_road_width;
    east_pos = screen.right;
    Road::autoPosition(screen);
};


void RightRoad::setLanes(RECT screen) {
    for (int i = 0; i < inboundLanes.size(); i++) {
        inboundLanes[i] = new RightLane(i, east_pos, north_pos + i * lane_width + (lane_width / 2), west_pos);
    }
    for (int i = 0; i < outboundLanes.size(); i++) {
        outboundLanes[i] = new OutboundLane(i);
    }
}