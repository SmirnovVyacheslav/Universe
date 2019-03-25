#pragma once
#include <windows.h>
#include <windowsx.h>
#include <memory>

#include"resource.h"

#include"engine.h"

using std::shared_ptr;
using std::unique_ptr;

//--------------------------------------------------------------------------------------
// Глобальные переменные
//--------------------------------------------------------------------------------------

HWND                    window;
HINSTANCE               instance;

int wnd_width = 533, wnd_height = 400;
int half_wnd_width = wnd_width / 2, half_wnd_height = wnd_height / 2;

unique_ptr<Engine> engine;

//--------------------------------------------------------------------------------------
// Объявления функций
//--------------------------------------------------------------------------------------
HRESULT          init_window(HINSTANCE inst, int cmd_show);
LRESULT CALLBACK msg_handler(HWND, UINT, WPARAM, LPARAM);