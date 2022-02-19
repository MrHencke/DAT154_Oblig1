#include "Car.h"
#include "Config.h"
Car::Car(int x_pos, int y_pos, Direction start) {
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->currentDirection = static_cast<Direction>((start + 2) % 4);
	this->start = start;
	this->destination = static_cast<Direction>((start + 2) % 4);
	this->size = car_size;
	this->speed = car_speed;
	this->color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void Car::draw(HDC hdc) {
    HBRUSH brush;
    brush = CreateSolidBrush(color); //randomize color
    HGDIOBJ hOrg = SelectObject(hdc, brush);
    RoundRect(hdc, (x_pos-size), (y_pos-size), (x_pos + size), (y_pos + size), 20, 20); 
    SelectObject(hdc, hOrg);
    DeleteObject(brush);
}

int Car::getYPos() {
	return y_pos;
}

int Car::getSize() {
	return size;
}

int Car::getXPos() {
	return x_pos;
}

Direction Car::getDestination() {
	return destination;
}


void Car::updatePosition() {
	switch (currentDirection)
	{
	case Direction::n:
		y_pos -= speed;
		break;
	case Direction::w:
		x_pos -= speed;
		break;
	case Direction::s:
		y_pos += speed;
		break;
	case Direction::e:
		x_pos += speed;
		break;
	}
}
