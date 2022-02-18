#include "Road.h"
#include "Colors.h"

void VerticalRoad::drawLaneDivider(HDC hdc) {
    Road::draw(hdc);
    LOGBRUSH lb;
    lb.lbColor = col_yellow;
    lb.lbStyle = PS_SOLID;
    HGDIOBJ hPen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 2, &lb, 0, NULL);
    HGDIOBJ hPenOrg = SelectObject(hdc, hPen);

    for (int i = 1; i < road_lanes; i++) {
        MoveToEx(hdc, i * lane_width + west_pos, north_pos, NULL);
        LineTo(hdc, i * lane_width + west_pos, south_pos);
    }

    SelectObject(hdc, hPenOrg);
    DeleteObject(hPen);
    DeleteObject(hPenOrg);
}
