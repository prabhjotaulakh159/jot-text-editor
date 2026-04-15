#include "app_state.h"

AppState *GetAppState(HWND hwnd) {
  LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
  AppState *appState = reinterpret_cast<AppState*>(ptr);
  return appState;
}
