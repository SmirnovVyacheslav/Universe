#pragma once
#include <windows.h>
#include <memory>

#include"resource.h"

#include"engine.h"

using std::shared_ptr;
using std::unique_ptr;

//--------------------------------------------------------------------------------------
// Глобальные переменные
//--------------------------------------------------------------------------------------

HWND                    hWnd;
HINSTANCE               hInst;

unique_ptr<Engine> engine;

//--------------------------------------------------------------------------------------
// Объявления функций
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);