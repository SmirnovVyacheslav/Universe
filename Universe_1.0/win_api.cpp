#include "win_api.h"

//#pragma comment(linker, "/STACK:20000000") // 20 mb

//--------------------------------------------------------------------------------------
// Главная функция программы. Происходят все инициализации, и затем выполняется
// цикл обработки сообщений
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE inst, HINSTANCE prev_inst, LPWSTR cmd_line, int cmd_show)
{
	UNREFERENCED_PARAMETER(inst);
	UNREFERENCED_PARAMETER(cmd_line);

	if (init_window(inst, cmd_show))
		return -1;

	engine.reset(new Engine(window));
	if (!engine->init())
		return -1;

	engine->start_render();

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
			//engine->render();
		}
	}

	engine->exit_render();

	return static_cast<int>(msg.wParam);
}


//--------------------------------------------------------------------------------------
// Создание окна
//--------------------------------------------------------------------------------------
HRESULT init_window(HINSTANCE inst, int cmd_show)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = msg_handler;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = inst;
	wcex.hIcon         = LoadIcon(inst, (LPCTSTR)IDI_ICON);
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = L"Header";
	wcex.hIconSm       = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	instance = inst;
	RECT rc = { 0, 0, wnd_width, wnd_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	window = CreateWindow(L"Header", L"Universe_1.0", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, inst, NULL);
	if (!window)
		return E_FAIL;

	ShowWindow(window, cmd_show);

	return S_OK;
}

void lock_cursor(HWND wnd)
{
	SetCapture(wnd);
	//ShowCursor(false);
	SetCursorPos(half_wnd_width, half_wnd_height);
}

void free_cursor(HWND wnd)
{
	ReleaseCapture();
	//ShowCursor(true);
}

//--------------------------------------------------------------------------------------
// Процедура обработки сообщений Windows
//--------------------------------------------------------------------------------------
LRESULT CALLBACK msg_handler(HWND wnd, UINT message, WPARAM w_param, LPARAM l_param)
{
	static bool alt = true;

	PAINTSTRUCT ps;
	HDC device_context;

	switch (message)
	{
	case WM_MOUSEMOVE:
		if (alt)
		{
			int x = GET_X_LPARAM(l_param);
			int y = GET_Y_LPARAM(l_param);

			if (half_wnd_width == x && half_wnd_height == y)
			{
				//camera_diff_x = 0;
				//camera_diff_y = 0;
				//sleep(0.1);
				break;
			}

			int diff_x = x - half_wnd_width;
			int diff_y = half_wnd_height - y;

			engine->moveCamera(diff_x, diff_y);

			POINT pt;
			pt.x = half_wnd_width;
			pt.y = half_wnd_height;
			ClientToScreen(wnd, &pt);
			SetCursorPos(pt.x, pt.y);
		}
			/*
			xPos = GET_X_LPARAM(lParam);
			yPos = GET_Y_LPARAM(lParam);
			*/
			//engine->moveCamera(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));

		break;
	case WM_PAINT:
		device_context = BeginPaint(wnd, &ps);
		EndPaint(wnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATE:
	{
		if (LOWORD(w_param) != WA_INACTIVE && alt)
		{
			lock_cursor(wnd);
		}
		else
		{
			free_cursor(wnd);
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
		switch (w_param)
		{
		case VK_MENU:
		{
			alt = alt ? false : true;
			if (alt)
			{
				lock_cursor(wnd);
			}
			else
			{
				free_cursor(wnd);
			}
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
		return DefWindowProc(wnd, message, w_param, l_param);
	}

	return 0;
}
