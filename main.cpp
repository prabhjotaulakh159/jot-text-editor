#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Signature different from docs since I'm using MinGW compiler
// https://www.transmissionzero.co.uk/computing/win32-apps-with-mingw/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  const wchar_t CLASS_NAME[] = L"Jot's Text Editor";
  const wchar_t WINDOW_NAME[] = L"Jot's Text Editor";
  
  WNDCLASS windowClass = {};
  windowClass.lpfnWndProc = WindowProc;
  windowClass.hInstance = hInstance;
  windowClass.lpszClassName = CLASS_NAME;
  RegisterClass(&windowClass);

  UINT8 NO_STYLES = 0;
  HWND window = CreateWindowEx(
    NO_STYLES, 
    CLASS_NAME, 
    WINDOW_NAME,
    WS_OVERLAPPEDWINDOW, 
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, 
    NULL, 
    hInstance, 
    NULL
  ); 

  ShowWindow(window, nCmdShow);

  MSG message = {};
  while (GetMessage(&message, NULL, 0, 0) > 0) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch(uMsg) {
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }

    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);
      FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
      EndPaint(hwnd, &ps);
      return 0;
    }
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}