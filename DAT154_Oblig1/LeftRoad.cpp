#include "framework.h"
#include "Road.h"
#include "Colors.h"
#include "Config.h"
#include "TrafficLight.h"
#include "Lane.h"


LeftRoad::LeftRoad() {
    this->direction = w;
    this->trafficLight = new TrafficLight(w);
}

void LeftRoad::draw(HDC hdc) {
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
            MoveToEx(hdc, west_pos, i * lane_width + north_pos, NULL);
            LineTo(hdc, east_pos, i * lane_width + north_pos);
        }

    SelectObject(hdc, hPenOrg);
    DeleteObject(hPen);
    DeleteObject(hPenOrg);

    Road::draw(hdc);

    for (const auto& car : cars) {
        car->draw(hdc);
    }

}

void LeftRoad::autoPosition(RECT screen) {
        north_pos = screen.bottom / 2 - h_road_width;
        east_pos = screen.right / 2 - h_road_width;
        south_pos = screen.bottom / 2 + h_road_width;

        Road::autoPosition(screen);
};

void LeftRoad::newCar(Direction destination) {
    cars.emplace_back(new Car(west_pos, north_pos + lane_width / 2, direction, destination));

}

void LeftRoad::updateCars() {
    int lastCarXPos = east_pos * 2;
    bool hasCarInFront = FALSE;
    for (std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++) {
        if ((*it)->getXPos() - car_size >= east_pos) {
            transferList.emplace_back(*it);
            cars.remove(*it);
            break;
        }
        hasCarInFront = it != cars.begin();
        int carXPos = (*it)->getXPos();
        if (carXPos > east_pos - 2 * car_size && carXPos < east_pos && (*it)->getDestination() != direction) {
            if (trafficLight->isGreen()) {
                (*it)->updatePosition();
            }
        }
        else if (hasCarInFront) {
            if (!(carXPos > lastCarXPos - (car_size + car_spacing) && carXPos < lastCarXPos)) {
                (*it)->updatePosition();
            }
        }
        else {
            (*it)->updatePosition();
        }
        lastCarXPos = (*it)->getXPos();
    }

}