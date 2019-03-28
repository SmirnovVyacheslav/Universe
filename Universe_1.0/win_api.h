#pragma once
#include <windows.h>
#include <windowsx.h>
#include <memory>

#include <thread>
#include <mutex>

#include"resource.h"

#include"engine.h"

/*40. Заголовочные файлы должны содержать защиту от вложенного включения.

#ifndef COM_COMPANY_MODULE_CLASSNAME_H
#define COM_COMPANY_MODULE_CLASSNAME_H
  :
#endif // COM_COMPANY_MODULE_CLASSNAME_H*/

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