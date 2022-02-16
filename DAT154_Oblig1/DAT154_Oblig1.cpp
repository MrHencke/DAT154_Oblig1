// DAT154_Oblig1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DAT154_Oblig1.h"
#include <iostream>
#include "TrafficController.h"
#define _USE_MATH_DEFINES
#include <Math.h>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

const WPARAM TL_Timer = 0;
const WPARAM UpdateCars_Timer = 1;

TrafficController trafficController;

//Forward declarations of functions
void clearScreen(HWND hWnd); 
void spawnSouthboundCar();
void spawnEastboundCar();
void incrementAllTrafficLights();
void updateCarPositions();
void debugLog(std::string message) {
    _RPT1(0, "%d\n", message);
}


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DAT154OBLIG1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DAT154OBLIG1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DAT154OBLIG1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DAT154OBLIG1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   SetTimer(hWnd, TL_Timer, 2000, NULL);
   SetTimer(hWnd, UpdateCars_Timer, 5, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT screen;
    GetClientRect(hWnd, &screen);

    switch (message)
    {
    case WM_CREATE:
        trafficController.positionAll(screen);
        break;
    case WM_SIZE:
        trafficController.positionAll(screen);
        break;
    case WM_SIZING:
        trafficController.positionAll(screen);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC ohdc = BeginPaint(hWnd, &ps);
        HDC hdc = CreateCompatibleDC(ohdc);
        HBITMAP bmp = CreateCompatibleBitmap(ohdc, screen.right, screen.bottom);
        SelectObject(hdc, bmp);
        HBRUSH bg = CreateSolidBrush(RGB(255, 255, 255));
        HGDIOBJ hOrg = SelectObject(hdc, bg);
        Rectangle(hdc, 0, 0, screen.right, screen.bottom);
        SelectObject(hdc, hOrg);
        DeleteObject(bg);
        trafficController.drawAll(hdc);
        BitBlt(ohdc, 0, 0, screen.right, screen.bottom, hdc, 0,0,SRCCOPY);
        DeleteObject(bmp);
        DeleteObject(hdc);
        EndPaint(hWnd, &ps);
        }
        break;
    case WM_TIMER:
        switch (wParam)
        {

        case TL_Timer:
            if (trafficController.incrementAllTrafficLights() == 0) {
                SetTimer(hWnd, TL_Timer, red_green_interval, NULL);
            }
            else {
                SetTimer(hWnd, TL_Timer, yellow_interval, NULL);
            }
            clearScreen(hWnd);
            break;
        case UpdateCars_Timer:
            trafficController.updateAllCars();
            clearScreen(hWnd);
            SetTimer(hWnd, UpdateCars_Timer, 1, NULL);
            break;
        default:
            break;
        }
        break;
    case WM_LBUTTONDOWN:
        trafficController.addCarToRoad(w, e);
        break;
    case WM_RBUTTONDOWN:
        trafficController.addCarToRoad(n, s);
        break;
    case WM_MBUTTONDOWN:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void clearScreen(HWND hWnd) {
    RECT screen;
    GetClientRect(hWnd, &screen);
    InvalidateRect(hWnd, &screen, FALSE);
}

