#include "Road.h"

void TopRoad::autoPosition(RECT screen) {
        west_pos = screen.right / 2 - h_road_width;
        east_pos = screen.right / 2 + h_road_width;
        south_pos = screen.bottom / 2 - h_road_width;
        Road::autoPosition(screen);
};

void TopRoad::setLanes(RECT screen) {
        for (int i = 0; i < inboundLanes.size(); i++) {
            inboundLanes[i] = new TopLane(i, west_pos + i * lane_width + (lane_width / 2), north_pos, south_pos);
        }
        for (int i = 0; i < outboundLanes.size(); i++) {
            outboundLanes[i] = new OutboundLane(north_pos);
        }
}