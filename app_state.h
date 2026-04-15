#include <string>
#include <windows.h>

namespace JotTextEditor_State {
  struct AppState {
    std::wstring currentFile;
  };

  AppState* GetAppState(HWND hwnd);
};

