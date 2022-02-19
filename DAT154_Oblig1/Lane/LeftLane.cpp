#include "Lane.h"

void LeftLane::updateCars(bool greenLight) {
    int lastCarXPos = inner * 2;
    for (std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++) {
        int carXPos = (*it)->getXPos();
        int carSize = (*it)->getSize();
        if ((*it)->getXPos() - carSize >= inner) {
            transferList.emplace_back(*it);
            cars.remove(*it);
            break;
        }
        bool hasCarInFront = it != cars.begin();
        if (carXPos > inner - 2 * carSize && carXPos < inner - carSize) {
            if (greenLight) {
                (*it)->updatePosition();
            }
        }
        else if (hasCarInFront) {
            if (!(carXPos > lastCarXPos - (carSize + car_spacing) && carXPos < lastCarXPos)) {
                (*it)->updatePosition();
            }
        }
        else {
            (*it)->updatePosition();
        }
        lastCarXPos = (*it)->getXPos();
    }
}