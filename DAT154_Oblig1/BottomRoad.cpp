#include "framework.h"
#include "Road.h"
#include "Colors.h"
#include "Config.h"
#include "TrafficLight.h"
#include "Lane.h"

BottomRoad::BottomRoad() {
    this->direction = s;
    this->trafficLight = new TrafficLight(s);
}

void BottomRoad::draw(HDC hdc) {
    LOGBRUSH lb;
    lb.lbColor = col_yellow;
    lb.lbStyle = PS_SOLID;
    HBRUSH brush = CreateSolidBrush(col_dark_gray);
    HGDIOBJ hOrg = SelectObject(hdc, brush);

    //Draw initial roads
    Rectangle(hdc, west_pos, north_pos, east_pos, south_pos);
    SelectObject(hdc, hOrg);
    DeleteObject(brush);
    WCHAR text[15];
    wsprintf(text, _T("%d"), direction);
    TextOut(hdc, west_pos, north_pos, text, wcslen(text));
    HGDIOBJ hPen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 2, &lb, 0, NULL);
    HGDIOBJ hPenOrg = SelectObject(hdc, hPen);


    for (int i = 1; i < road_lanes; i++) {
        MoveToEx(hdc, i * lane_width + west_pos, north_pos, NULL);
        LineTo(hdc, i * lane_width + west_pos, south_pos);
    }

    SelectObject(hdc, hPenOrg);
    DeleteObject(hPen);
    DeleteObject(hPenOrg);

    Road::draw(hdc);


    for (auto car : cars) {
        car->draw(hdc);
    }
}
void BottomRoad::autoPosition(RECT screen) {
    west_pos = screen.right / 2 - h_road_width;
    east_pos = screen.right / 2 + h_road_width;
    north_pos = screen.bottom / 2 + h_road_width;
    south_pos = screen.bottom;
    Road::autoPosition(screen);
};

void BottomRoad::newCar(Direction destination) {
    cars.emplace_back(new Car(east_pos - lane_width / 2, south_pos, direction, destination));
}


void BottomRoad::updateCars() {
    int lastCarYPos = north_pos/2;
    bool hasCarInFront = FALSE;
    for (std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++) {
        if ((*it)->getYPos() <= north_pos) {
            transferList.emplace_back(*it);
            cars.remove(*it);
            break;
        }
        hasCarInFront = it != cars.begin();
        int carYPos = (*it)->getYPos();
        if (carYPos < north_pos + 2 * car_size && carYPos > north_pos && (*it)->getDestination() != direction) {
            if (trafficLight->isGreen()) {
                (*it)->updatePosition();
            }
        }
        else if (hasCarInFront) {
            if (!(carYPos < lastCarYPos + (car_size + car_spacing) && carYPos > lastCarYPos) ) {
                (*it)->updatePosition();
            }
        }
        else {
            (*it)->updatePosition();
        }
        lastCarYPos = (*it)->getYPos();
    }
}