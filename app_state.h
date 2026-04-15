#include <string>
#include <windows.h>

struct AppState {
  std::wstring currentFile;
};

AppState* GetAppState(HWND hwnd);


