#pragma once
#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>

const int road_lanes = 2;
const int lane_width = 70;// 35;

const int red_green_interval_S = 5;
const int yellow_interval_S = 2;



enum Direction {
	n=0, w, s, e
};
/*
 const void debugLog(std::string message) {
	_RPT1(0, "%d\n", message);
}*/

//Calculated constants
const int road_width = road_lanes * lane_width;
const int h_road_width = road_width / 2;

const int red_green_interval = red_green_interval_S * 1000;
const int yellow_interval = yellow_interval_S * 1000;


#endif