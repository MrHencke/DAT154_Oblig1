#include "framework.h"
#include "Road.h"
#include "Colors.h"
#include "Config.h"
#include "TrafficLight.h"
#include "Lane.h"


Road::Road(Direction direction) {
    this->cars = std::list<Car*>();
    this->transferList = std::list<Car*>();
    this->direction = direction;
    this -> west_pos = 0;
    this -> north_pos = 0;
    this -> east_pos = 0;
    this -> south_pos = 0;
}

void Road :: draw(HDC hdc) {
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

    
    if (direction == Direction::n || direction == Direction::s) {
        for (int i = 1; i < road_lanes; i++) {
            MoveToEx(hdc, i * lane_width + west_pos, north_pos, NULL);
            LineTo(hdc, i * lane_width + west_pos, south_pos);
        }
    }
    else {
        for (int i = 1; i < road_lanes; i++) {
            MoveToEx(hdc, west_pos, i * lane_width + north_pos, NULL);
            LineTo(hdc, east_pos, i * lane_width + north_pos);
        }
    }
    
    SelectObject(hdc, hPenOrg);
    DeleteObject(hPen);
    DeleteObject(hPenOrg);
 
    for (const auto& car : cars) {
        car->draw(hdc);
    }

}
//Only refreshes a road if it has cars.
void Road::refresh(HWND hWnd){
    if(cars.size() > 0 || transferList.size()>0) {
    RECT roadArea = { west_pos, north_pos, east_pos, south_pos };
    InvalidateRect(hWnd, &roadArea, TRUE);
    }
}

void Road::autoPosition(RECT screen) {
    switch (direction) {
    case Direction::n:
        west_pos = screen.right / 2 - h_road_width;
        east_pos = screen.right / 2 + h_road_width;
        south_pos = screen.bottom / 2 - h_road_width;
        break;
    case Direction::w:
        north_pos = screen.bottom / 2 - h_road_width;
        east_pos = screen.right / 2 - h_road_width;
        south_pos = screen.bottom / 2 + h_road_width;
        break;
    case Direction::s:
        west_pos = screen.right / 2 - h_road_width;
        east_pos = screen.right / 2 + h_road_width;
        north_pos = screen.bottom / 2 + h_road_width;
        south_pos = screen.bottom;
        break;
    case Direction::e:
        west_pos = screen.right / 2 + h_road_width;
        north_pos = screen.bottom / 2 - h_road_width;
        south_pos = screen.bottom / 2 + h_road_width;
        east_pos = screen.right;
        break;
    default:
        break;
    }
};

void Road::newCar(Direction destination) {
    if (direction == n || direction == s) {
        cars.insert(cars.begin(), new Car(west_pos + lane_width / 2, north_pos, direction, destination, 20, car_speed));
    }
    else {
        cars.insert(cars.begin(), new Car(west_pos, north_pos+lane_width/2, direction, destination, 20, car_speed));
    }
}

void Road::addCar(Car*car) {
    cars.emplace_front(car);
}

void Road::updateCars() {
    for (std::list<Car*>::reverse_iterator it = cars.rbegin(); it != cars.rend();) {
        (*it)->updatePosition();

        switch (direction)
        {
        case n:
            if ((*it)->getYPos() + (*it)->getSize() >= south_pos) {
                transferList.emplace_front(*it);
                cars.remove(*it);
            }
            else it++;
            break;
        case w:
            if ((*it)->getXPos() + (*it)->getSize() >= east_pos) {
                transferList.emplace_front(*it);
                cars.remove(*it);
            }
            else it++;
            break;
        case s:
            if ((*it)->getYPos() - (*it)->getSize() >= north_pos) {
                transferList.emplace_front(*it);
                cars.remove(*it);
            }
            else it++;
            break;
        case e:
            if ((*it)->getXPos() - (*it)->getSize() >= west_pos) {
                transferList.emplace_front(*it);
                cars.remove(*it);
            }
            else it++;
            break;
        default:
            break;
        }
        //it++;
    }

}    


std::list<Car*> Road::getTransferList() {
    return transferList;
}

void Road::clearTransferList() {
    transferList = {};
}


void Road::moveToTransferList() {
    //Fix later
    //transferList.emplace_front(*it);
    //cars.remove(*it);

}              