#include "Road.h"

void BottomRoad::autoPosition(RECT screen) {
    west_pos = screen.right / 2 - h_road_width;
    east_pos = screen.right / 2 + h_road_width;
    north_pos = screen.bottom / 2 + h_road_width;
    south_pos = screen.bottom;
    Road::autoPosition(screen);
};

void BottomRoad::setLanes(RECT screen) {
    for (int i = 0; i < inboundLanes.size();i++) {
        inboundLanes[i] = new BottomLane(i, east_pos - (i+1) * lane_width + (lane_width / 2), south_pos, north_pos);
    }    
    for (int i = 0; i < outboundLanes.size();i++) {
        outboundLanes[i] = new OutboundLane(south_pos);
    }
}