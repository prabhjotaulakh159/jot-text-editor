#include "app_state.h"

JotTextEditor_State::AppState *JotTextEditor_State::GetAppState(HWND hwnd) {
  LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
  JotTextEditor_State::AppState *appState = reinterpret_cast<JotTextEditor_State::AppState*>(ptr);
  return appState;
}
