#ifndef UNICODE
#define UNICODE
#endif 

#define JOT_TEXT_EDITOR_MENU_SAVE_ID 1000
#define JOT_TEXT_EDITOR_MENU_OPEN_ID 1001

#include <windows.h>
#include "file_loader.h"
#include <iostream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HMENU JotTextEditorCreateMenu();

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
  static JotTextEditor::FileLoader fileLoader;
  
  switch(uMsg) { 
    case WM_CREATE: {
      // testing for now
      if (!fileLoader.readFileIntoLines("test.txt")) {
        std::cout << "fail" << std::endl;
      }
      else {
        std::cout << "good";
        std::cout << fileLoader.getLines().size();
      }
      for(std::string line: fileLoader.getLines()) {
        std::cout << line << std::endl;
      }

      HMENU menu = CreateMenu();
      AppendMenu(menu, MF_STRING, JOT_TEXT_EDITOR_MENU_SAVE_ID, L"Save");
      AppendMenu(menu, MF_STRING, JOT_TEXT_EDITOR_MENU_OPEN_ID, L"Open");
      SetMenu(hwnd, menu);
      return 0;
    }

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