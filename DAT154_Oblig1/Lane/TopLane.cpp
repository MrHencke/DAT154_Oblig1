#include "Lane.h"

void TopLane::updateCars(bool greenLight) {
    int lastCarYPos = inner * 2;
    for (std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++) {
        int carYPos = (*it)->getYPos();
        int carSize = (*it)->getSize();
        if ((*it)->getYPos() - carSize >= inner) {
            transferList.emplace_back(*it);
            cars.remove(*it);
            break;
        }
        bool hasCarInFront = it != cars.begin();
        if (carYPos > inner - 2 * carSize && carYPos < inner - carSize) {
            if (greenLight) {
                (*it)->updatePosition();
            }
        }
        else if (hasCarInFront) {
            if (!(carYPos > lastCarYPos - (carSize + car_spacing) && carYPos < lastCarYPos)) {
                (*it)->updatePosition();
            }
        }
        else {
            (*it)->updatePosition();
        }
        lastCarYPos = (*it)->getYPos();
    }
}