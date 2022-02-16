#include "TrafficLight.h"
#include "Colors.h"
#include "framework.h"
#include "Config.h"

    bool states[4][3] = {
           {TRUE, FALSE, FALSE},
           { TRUE, TRUE, FALSE },
           { FALSE, FALSE, TRUE },
           { FALSE, TRUE, FALSE } };

    bool* getLightState(int state) {
        return states[state];
    }
    TrafficLight::TrafficLight() {
        this->direction = Direction::n;
        this->west_pos = 0;
        this->north_pos = 0;
        this->east_pos = 0;
        this->south_pos = 0;
        this->state = 0;
    }
    TrafficLight::TrafficLight(Direction direction) {
        this->direction = direction;
        this -> west_pos = 0;
        this -> north_pos = 0;
        this -> east_pos = 0;
        this -> south_pos = 0;
        this->state = 0;
    }

	void TrafficLight::draw(HDC hdc) {
        HBRUSH brush;
        bool * lightState = getLightState(state);
        brush = CreateSolidBrush(col_black);
        HGDIOBJ hOrg = SelectObject(hdc, brush);
        RoundRect(hdc, west_pos, north_pos, east_pos, south_pos, 20, 20); //Background
        SelectObject(hdc, hOrg);
        DeleteObject(brush);
        for (int i = 0; i < 3; i++) {
            int j = i + 1;
            int left = west_pos + tl_margin;
            int top = north_pos + tl_margin + i * tl_width;
            int right = east_pos - tl_margin;
            int bottom = north_pos + ((j * tl_width)) - tl_margin;
            if (lightState[i]) {
                brush = CreateSolidBrush(t_light[i]);
            }
            else {
                brush = CreateSolidBrush(col_gray);
            }
            SelectObject(hdc, brush);

            Ellipse(hdc, left, top, right, bottom);
            SelectObject(hdc, hOrg);
            DeleteObject(brush);
        WCHAR text[15];
        wsprintf(text, _T("%d"), state);
        TextOut(hdc, west_pos, north_pos, text, wcslen(text));
        }
	}
    int TrafficLight::getState() {
        return state;
    }
    bool TrafficLight::isGreen() {
        return state == 2;
    }
    void TrafficLight::setState(int x) {
        state = x;
    }
    void TrafficLight::incState() {
        state = (state + 1) % 4;
    };

    void TrafficLight::autoPosition(RECT screen) {

        switch (direction) {
            case Direction::n:
                west_pos = screen.right / 2 - h_road_width - tl_width - tl_margin;
                north_pos = screen.bottom / 2 - h_road_width - tl_height - tl_margin;
                break;
            case Direction::w:
                west_pos = screen.right/2 - 3*tl_width;
                north_pos = screen.bottom/2 + h_road_width + tl_margin;
                break;
            case Direction::s:
                west_pos = screen.right / 2 + h_road_width + tl_margin;
                north_pos = screen.bottom / 2 + h_road_width + tl_margin;
                break;
            case Direction::e:
                west_pos = screen.right / 2 + h_road_width + tl_width + tl_margin;
                north_pos = screen.bottom / 2 - h_road_width - tl_height - tl_margin;
                break;
            default:
                west_pos = 0;
                north_pos = 0;
                break;
        }
        east_pos = west_pos + tl_width;
        south_pos = north_pos + tl_height;
    };
    void TrafficLight::refresh(HWND hWnd) {
        RECT tl_area = { west_pos, north_pos, east_pos, south_pos };
        InvalidateRect(hWnd, &tl_area, TRUE);
    };





