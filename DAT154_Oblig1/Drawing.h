#pragma once
#include "framework.h"

#ifndef DRAWROADS_H
#define DRAWROADS_H
void drawRoads(HDC hdc, RECT screen);

void drawTrafficLight(HDC hdc, int x, int y, bool * stateArr);
#endif