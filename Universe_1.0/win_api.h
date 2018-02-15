#pragma once
#include <windows.h>
#include <memory>

#include"resource.h"

#include "dx_11.h"
#include "geometry.h"

//--------------------------------------------------------------------------------------
// Глобальные переменные
//--------------------------------------------------------------------------------------

HWND                    hWnd;
HINSTANCE               hInst;


std::unique_ptr<dx_11> device;
std::shared_ptr<Geometry> geometry;
std::shared_ptr<Camera> camera;

//--------------------------------------------------------------------------------------
// Объявления функций
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);