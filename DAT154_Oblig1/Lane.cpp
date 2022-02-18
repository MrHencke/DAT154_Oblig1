#include "Lane.h"

Lane::Lane() {
	this->x_pos = 0;
	this->y_pos = 0;
	this->inbound = TRUE;
}

Lane::Lane(int x, int y, bool inbound) {
	this->x_pos = x;
	this->y_pos = y;
	this->inbound = inbound;
	this->cars = std::list<Car*>();
}

int Lane::getXPos() {
	return x_pos;
}

void Lane::setXPos(int x){
	x_pos = x;
}

int Lane::getYPos(){
	return y_pos;
}

void Lane::setYPos(int y){
	y_pos = y;
}




