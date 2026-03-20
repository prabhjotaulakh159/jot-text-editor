/**
 * Docs reference :)
 * 
 * How to create a window for input area: https://learn.microsoft.com/en-us/windows/win32/controls/use-a-multiline-edit-control
 * Basic setup win32: https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
 * MinGW win32 setup: https://www.transmissionzero.co.uk/computing/win32-apps-with-mingw/
 * Mouse click detection: https://stackoverflow.com/questions/2522029/how-to-handle-click-event-in-win32-api
 * Opening dialog boxes: https://iq.direct/blog/57-displaying-open-file-dialog-using-winapi.html
 */

#ifndef UNICODE
#define UNICODE
#endif 

#define JOT_TEXT_EDITOR_MENU_OPEN_ID 1000
#define JOT_TEXT_EDITOR_MENU_SAVE_ID 1001

#define JOT_TEXT_EDITOR_EDIT_WINDOW_ID 2000

#include <windows.h>
#include "file_loader.h"
#include <iostream>
#include <commdlg.h>

namespace JotTextEditor_IO {
  HMENU SetupBasicMenu() {
    HMENU menu = CreateMenu();
    AppendMenu(menu, MF_STRING, JOT_TEXT_EDITOR_MENU_OPEN_ID, L"Open");
    AppendMenu(menu, MF_STRING, JOT_TEXT_EDITOR_MENU_SAVE_ID, L"Save");
    return menu;
  } 

  HWND SetupInputArea(const HWND& parent) {
    return CreateWindowEx(
      0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 
      0, 0, 0, 0, parent, (HMENU) JOT_TEXT_EDITOR_EDIT_WINDOW_ID, (HINSTANCE) GetWindowLongPtr(parent, GWLP_HINSTANCE), 
      NULL);
  }

  void ShowWelcomeMessage(const HWND& editArea) {
    std::wstring welcomeMsg = L"Welcome to Jot Text Editor! Try to open a file";
    SendMessage(editArea, WM_SETTEXT, 0, (LPARAM) welcomeMsg.c_str());
  }

  void OutputFileContentOnEditArea(const HWND& editArea, std::vector<std::wstring>& lines) {
    std::wstring content;
    for (std::wstring& line : lines) {
      content.append(line);
      content.append(L"\r\n");
    }
    SendMessage(editArea, WM_SETTEXT, 0, (LPARAM) content.c_str());
  }

  bool GetFileFromFileChooser(const HWND& parent, std::wstring& out) {
    std::wstring filename;

    OPENFILENAME ofn = {0}; 
    TCHAR szFile[MAX_PATH]={0};
    
    ofn.lStructSize = sizeof(ofn); 
    ofn.hwndOwner = parent; 
    ofn.lpstrFile = szFile; 
    ofn.nMaxFile = sizeof(szFile); 
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1; 
    ofn.lpstrFileTitle = NULL; 
    ofn.nMaxFileTitle = 0; 
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if(GetOpenFileName(&ofn) == TRUE)
    { 
      out = szFile;
      return true;
    }

    return false;
  }
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
  static JotTextEditor_IO::FileLoader fileLoader;
  static HWND editArea;
  static HMENU menu;

  switch(uMsg) { 
    case WM_CREATE: {
      menu = JotTextEditor_IO::SetupBasicMenu();
      editArea = JotTextEditor_IO::SetupInputArea(hwnd);
      SetMenu(hwnd, JotTextEditor_IO::SetupBasicMenu());
      JotTextEditor_IO::ShowWelcomeMessage(editArea);
      return 0;
    }

    case WM_SIZE: {
      MoveWindow(editArea, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE); 
      return 0;
    }

    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }

    case WM_COMMAND: {
      if (LOWORD(wParam) == JOT_TEXT_EDITOR_MENU_OPEN_ID) {
        std::wstring filename;
        if (JotTextEditor_IO::GetFileFromFileChooser(hwnd, filename)) {
          fileLoader.readFileIntoLines(filename);
          JotTextEditor_IO::OutputFileContentOnEditArea(editArea, fileLoader.getLines());
        } 
      }
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