#include "win_api.h"

//#pragma comment(linker, "/STACK:20000000") // 20 mb

//--------------------------------------------------------------------------------------
// Главная функция программы. Происходят все инициализации, и затем выполняется
// цикл обработки сообщений
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (InitWindow(hInstance, nCmdShow))
		return -1;

	engine.reset(new Engine(hWnd));
	if (!engine->init())
		return -1;

	// Цикл обработки сообщений
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			engine->render();
		}
	}

	return static_cast<int>(msg.wParam);
}


//--------------------------------------------------------------------------------------
// Создание окна
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_ICON);
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = L"Header";
	wcex.hIconSm       = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	hInst = hInstance;
	RECT rc = { 0, 0, 533, 400 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(L"Header", L"Universe_1.0", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return E_FAIL;

	ShowWindow(hWnd, nCmdShow);

	return S_OK;
}


void lockCursor(HWND hWnd)
{
	RECT rc;
	GetWindowRect(hWnd, &rc);

	ClipCursor(&rc);
	SetCursorPos(int(rc.right / 2), int(rc.bottom / 2));
	ShowCursor(false);
}

void freeCursor(HWND hWnd)
{
	RECT rc;
	ShowCursor(true);
	ClipCursor(NULL);
}

//--------------------------------------------------------------------------------------
// Процедура обработки сообщений Windows
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rc;
	static bool alt = true;

	switch (message)
	{
	case WM_MOUSEMOVE:
		if (alt)
			engine->moveCamera(static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam)));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) != WA_INACTIVE && alt)
		{
			lockCursor(hWnd);
		}
		else
		{
			freeCursor(hWnd);
		}
	} break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		/*switch (wParam)
		{
		
		}*/
	}
	break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		switch (wParam)
		{
		case VK_MENU:
		{
			alt = alt ? false : true;
			if (alt)
				lockCursor(hWnd);
			else
				freeCursor(hWnd);
		}
			break;
		}
	}
	break;

	case WM_SIZE:
	{
		if (engine)
			engine->resize();
	}
	break;

	case WM_MOVE:
	{
		if (engine)
			engine->resize();
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
