#include "../framework.h"
#include "Road.h"
#include "../Colors.h"
#include "../TrafficLight.h"

void HorizontalRoad::drawLaneDivider(HDC hdc) {
    Road::draw(hdc);
    for (int i = 1; i < road_lanes; i++) {
    LOGBRUSH lb;
    lb.lbColor = i == road_lanes/2 ? col_yellow : col_white;
    lb.lbStyle = PS_SOLID;
    HGDIOBJ hPen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 2, &lb, 0, NULL);
    HGDIOBJ hPenOrg = SelectObject(hdc, hPen);
        MoveToEx(hdc, west_pos, i * lane_width + north_pos, NULL);
        LineTo(hdc, east_pos, i * lane_width + north_pos);
    SelectObject(hdc, hPenOrg);
    DeleteObject(hPen);
    DeleteObject(hPenOrg);
    }
}
