#include "../framework.h"
#include "Road.h"
#include "../Colors.h"
#include "../TrafficLight.h"

void HorizontalRoad::drawLaneDivider(HDC hdc) {
    Road::draw(hdc);
    LOGBRUSH lb;
    lb.lbColor = col_yellow;
    lb.lbStyle = PS_SOLID;
    HGDIOBJ hPen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 2, &lb, 0, NULL);
    HGDIOBJ hPenOrg = SelectObject(hdc, hPen);
    for (int i = 1; i < road_lanes; i++) {
        MoveToEx(hdc, west_pos, i * lane_width + north_pos, NULL);
        LineTo(hdc, east_pos, i * lane_width + north_pos);
    }
    SelectObject(hdc, hPenOrg);
    DeleteObject(hPen);
    DeleteObject(hPenOrg);
}
