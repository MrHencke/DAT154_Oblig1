#pragma once
#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>

const int road_lanes = 4;
const int lane_width = 70;
const int red_green_interval_S = 5;
const int yellow_interval_S = 2;
const int cars_timer_interval = 10; //Update car position every 10ms

enum Direction {
	n=0, w, s, e
};

//Calculated constants
const int road_width = road_lanes * lane_width;
const int h_road_width = road_width / 2;
const int red_green_interval = red_green_interval_S * 1000;
const int yellow_interval = yellow_interval_S * 1000;


#endif