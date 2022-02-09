#include "Drawing.h"
#include "framework.h"
#include "Colors.h"


void drawRoads(HDC hdc, RECT screen) {
    int lane_width = 25;
    int road_width = 3*lane_width;
    HBRUSH brush = CreateSolidBrush(col_gray);
    HGDIOBJ hOrg = SelectObject(hdc, brush);


    //Draw initial roads
    Rectangle(hdc, screen.left, screen.bottom/2-road_width, screen.right, screen.bottom/2 + road_width); //Horizontal
    Rectangle(hdc, screen.right/2 - road_width, screen.top, screen.right/2 + road_width, screen.bottom); //Vertical
    SelectObject(hdc, hOrg);
    DeleteObject(brush);
    for (int i = 1; i < 3; i++) {
    //Draw lanes on horizontal road
    MoveToEx(hdc, screen.left, screen.bottom / 2-road_width+ i * 2*lane_width, NULL);
    LineTo(hdc,screen.right, screen.bottom / 2 - road_width + i * 2*lane_width);
    //Draw lanes on vertical road
    MoveToEx(hdc, screen.right/2 -road_width+ i*2*lane_width, screen.top, NULL);
    LineTo(hdc, screen.right/2 - road_width + i*2 * lane_width, screen.bottom);
    }

    //Center square
    brush = CreateSolidBrush(col_dark_gray);
    SelectObject(hdc, brush);
    Rectangle(hdc, screen.right / 2 - road_width, screen.bottom / 2 - road_width, screen.right / 2 + road_width, screen.bottom / 2 + road_width); //top to bottom road
    SelectObject(hdc, hOrg);
    DeleteObject(brush);
    
}



void drawVehicle(HDC hdc, int state) {


}


