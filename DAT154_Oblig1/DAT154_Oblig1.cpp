#include "DAT154_Oblig1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
const WPARAM TL_Timer = 0;
const WPARAM UpdateCars_Timer = 1;
const WPARAM SpawnCars_Timer = 2;
int pw=0;
int pn=0;
TrafficController trafficController;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Settings(HWND, UINT, WPARAM, LPARAM);
void clearScreen(HWND hWnd); 
void writePW(HDC hdc, RECT screen, int pw);
void writePN(HDC hdc, RECT screen, int pn);
void writeDebugProbabilities(HDC hdc, RECT screen, int pw, int pn);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

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

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   //Initialize timers
   SetTimer(hWnd, TL_Timer, yellow_interval, NULL);
   SetTimer(hWnd, UpdateCars_Timer, cars_timer_interval, NULL);
   SetTimer(hWnd, SpawnCars_Timer, 1000, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//Main window procedure
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
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_P_SETTINGS:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGSBOX), hWnd, Settings);
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
        HBRUSH bg = CreateSolidBrush(RGB(39, 98, 0));
        HGDIOBJ hOrg = SelectObject(hdc, bg);
        Rectangle(hdc, 0, 0, screen.right, screen.bottom);
        writeDebugProbabilities(hdc, screen, pw, pn);
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
        switch (wParam){
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
            SetTimer(hWnd, UpdateCars_Timer, cars_timer_interval, NULL);
            break;
        case SpawnCars_Timer: 
            if (rand() % 100 + 1 <= pw) {
                trafficController.addCarToRoad(w, e);
            }
            if (rand() % 100 + 1 <= pn) {
                trafficController.addCarToRoad(n, s);
            }
            SetTimer(hWnd, SpawnCars_Timer, 1000, NULL);
            break;
        }
        break;
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_UP:
            pn = pn >= 100 ? 100 : pn + 10;
            break;
        case VK_DOWN:
            pn = pn <= 0 ? 0 : pn - 10;
            break;
        case VK_LEFT:
            pw = pw <= 0 ? 0 : pw - 10;
            break;
        case VK_RIGHT:
            pw = pw >= 100 ? 100 : pw + 10;
            break;
        case 0x57: //W key
            trafficController.addCarToRoad(n, s);
            break;
        case 0x41: //A key
            trafficController.addCarToRoad(w, e);
            break;
        case 0x53: //S key
            trafficController.addCarToRoad(s, n);
            break;
        case 0x44: //S key
            trafficController.addCarToRoad(e, w);
            break;
        }
        break;
    case WM_LBUTTONDOWN:
        trafficController.addCarToRoad(w, e);
        break;
    case WM_RBUTTONDOWN:
        trafficController.addCarToRoad(n, s);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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

INT_PTR CALLBACK Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        //TODO Set value in input field to current value;
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }

        if (LOWORD(wParam) == IDOK) {
            //TODO Add check if value is above 100.
            pw = GetDlgItemInt(hDlg, IDC_PW_FIELD, NULL, FALSE);
            pn = GetDlgItemInt(hDlg, IDC_PN_FIELD, NULL, FALSE);
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

void writeDebugProbabilities(HDC hdc, RECT screen, int pw, int pn) {
    writePW(hdc, screen, pw);
    writePN(hdc, screen, pn);
}

void writePW(HDC hdc, RECT screen, int pw) {
    TCHAR text[30];
    wsprintf(text, _T("PW: %d%%"), pw);
    TextOut(hdc, screen.left, screen.top, text, wcslen(text));
}

void writePN(HDC hdc, RECT screen, int pn) {
    TCHAR text[30];
    wsprintf(text, _T("PN: %d%%"), pn);
    TextOut(hdc, screen.left, screen.top + 20, text, wcslen(text));
}