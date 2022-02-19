#include "Intersection.h"
#include "framework.h"
#include "Road/Road.h"
#include "Colors.h"
#include "Config.h"

Intersection::Intersection() {
    this->cars = std::list<Car*>();
    this->transferList = std::list<Car*>();
    this->west_pos = 0;
    this->north_pos = 0;
    this->east_pos = 0;
    this->south_pos = 0;
}

void Intersection::draw(HDC hdc){
    HBRUSH brush = CreateSolidBrush(col_darker_gray);
    HGDIOBJ hOrg = SelectObject(hdc, brush);
    Rectangle(hdc, west_pos, north_pos, east_pos, south_pos);
    SelectObject(hdc, hOrg);
    DeleteObject(brush);
    for (auto car : cars){
        car->draw(hdc);
    }
}

void Intersection::autoPosition(RECT screen) {
    int x_pos = screen.right / 2;
    int y_pos = screen.bottom / 2;
    west_pos = x_pos - h_road_width;
    north_pos = y_pos - h_road_width;
    east_pos = x_pos + h_road_width;
    south_pos = y_pos + h_road_width;
};

void Intersection::updateCars() {
    for (std::list<Car*>::reverse_iterator it = cars.rbegin(); it != cars.rend();) {
        (*it)->updatePosition();
        switch ((*it)->getDestination())
        {
        case n:
            if ((*it)->getYPos()-car_size <= north_pos) {
                transferList.emplace_front(*it);
                cars.remove(*it);
            }
            else {
                it++;
            }
            break;
        case w:
            if ((*it)->getXPos() - car_size <= west_pos) {
                transferList.emplace_front(*it);
                cars.remove(*it);
            }
            else {
                it++;
            }
            break;
        case s:
            if ((*it)->getYPos() + car_size >= south_pos) {
                transferList.emplace_front(*it);
                cars.remove(*it);
            }
            else {
                it++;
            }
            break;
        case e:
            if ((*it)->getXPos() + car_size >= east_pos) {
                transferList.emplace_front(*it);
                cars.remove(*it);
            }
            else {
                it++;
            }
            break;
        default:
            break;
        }
    }
}


std::list<Car*> Intersection::getTransferList() {
    return transferList;
}

void Intersection::clearTransferList() {
    transferList = {};
}

void Intersection::addCars(std::list<Car*> transferred) {
    cars.splice(cars.end(), transferred);
}