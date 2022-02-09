// DAT154_Oblig1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DAT154_Oblig1.h"
#include "Drawing.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <Math.h>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//bool initState[3] = { TRUE, FALSE, FALSE };
bool lightStates[4][3] = {{TRUE, FALSE, FALSE}};

int state = 0;

void setState(int state, int light);
void clearScreen(HWND hWnd);
void replaceRow(int light, bool newState[]);
void debugState(HDC hdc);
void debugLightState(HDC hdc);

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
    switch (message)
    {
       
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
        RECT screen;
        GetClientRect(hWnd, &screen);
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        debugState(hdc);
        debugLightState(hdc);
        drawRoads(hdc, screen); //  traffic flow: (top->bottom, left->right)
        drawTrafficLight(hdc, screen.right/2 + 100, screen.bottom/2 - 450, lightStates[0]);
        drawTrafficLight(hdc, screen.right/2 - 250, screen.bottom/2 + 100, lightStates[1]);
        //drawTrafficLight(hdc, 300, 200, lightStates[2]);
        //drawTrafficLight(hdc, 100, 200, lightStates[3]);
        EndPaint(hWnd, &ps);
        }
        break;
    case WM_LBUTTONDOWN:
        state = (state + 1) % 4;
        setState(state, 0);
        setState(state, 1);
        setState(state, 2);
        setState(state, 3);

        clearScreen(hWnd);
        break;
    case WM_MBUTTONDOWN: //For debugging purposes
        clearScreen(hWnd);
        break;
    case WM_RBUTTONDOWN:
        state = state == 0 ? 3 : state-1;
        setState(state, 0);
        clearScreen(hWnd);
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

void setState(int state, int light) {
    switch (state) {
    case 0:
        replaceRow(light, new bool[3] { TRUE, FALSE, FALSE });
        break;
    case 1:
        replaceRow(light, new bool[3]{ TRUE, TRUE, FALSE });
        break;
    case 2:
        replaceRow(light, new bool[3]{ FALSE, FALSE, TRUE });
        break;
    case 3:
        replaceRow(light, new bool[3]{ FALSE, TRUE, FALSE });
        break;
    default:
        replaceRow(light, new bool[3]{ TRUE, FALSE, FALSE });
        break;
    }
}

void replaceRow(int light, bool newState[]) {
    for (int i = 0; i < 3; i++) {
        lightStates[light][i] = newState[i];
    }
}
void clearScreen(HWND hWnd) {
    RECT screen;
    GetClientRect(hWnd, &screen);
    InvalidateRect(hWnd, &screen, TRUE);
}

void debugState(HDC hdc) {
        WCHAR s[10];
        _itow_s(state, s, 10);
        s[9] = '\0';
        TextOut(hdc, 100, 100, s, wcslen(s));
    
}

void debugLightState(HDC hdc) {
    for (int i = 0; i < 3; i++)
    {
        if (lightStates[0][i]) {
        WCHAR s[10];
        _itow_s(i, s, 10);
        s[9] = '\0';
        TextOut(hdc, i*100, 150, s, wcslen(s));
        }
    }

}
