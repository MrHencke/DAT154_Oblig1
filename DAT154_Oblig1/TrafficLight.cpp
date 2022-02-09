#include "TrafficLight.h"
#include "Colors.h"
#include "framework.h"

    bool states[4][3] = {
           {TRUE, FALSE, FALSE},
           { TRUE, TRUE, FALSE },
           { FALSE, FALSE, TRUE },
           { FALSE, TRUE, FALSE } };

        bool* getLightState(int state) {
            return states[state];
        }

        TrafficLight::TrafficLight()
            : x_pos(0), y_pos(0), state(0)
        {}

        TrafficLight::TrafficLight(const int x, const int y)
            : x_pos(x), y_pos(y), state(0)
        {}

		void TrafficLight::draw(HDC hdc) {
            HBRUSH brush;
            bool * lightState = getLightState(state);
            brush = CreateSolidBrush(col_black);
            HGDIOBJ hOrg = SelectObject(hdc, brush);
            RoundRect(hdc, x_pos, y_pos, (x_pos + width), (y_pos + height), 20, 20); //Background
            SelectObject(hdc, hOrg);
            DeleteObject(brush);
            for (int i = 0; i < 3; i++) {
                int j = i + 1;
                int left = x_pos + margin;
                int top = y_pos + margin + i * width;
                int right = (x_pos + width) - margin;
                int bottom = y_pos + ((j * width)) - margin;
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
            }
		}
        int TrafficLight::getState() {
            return state;
        }
        void TrafficLight::setState(int x) {
            state = x;
        }
        void TrafficLight::incState() {
            state = (state + 1) % 4;
        };
        void TrafficLight::decState() {
            state = state == 0 ? 3 : state - 1;
        };
        void TrafficLight::setCoords(int x, int y) {
            x_pos = x;
            y_pos = y;
        };
        void TrafficLight::refresh(HWND hWnd) {
            RECT tl_area = { x_pos, y_pos, (x_pos + width), (y_pos + height) };
            InvalidateRect(hWnd, &tl_area, TRUE);
        };
        void TrafficLight::setX(int x) {
            x_pos = x;
        };
        void TrafficLight::setY(int y) {
            y_pos = y;
        };





