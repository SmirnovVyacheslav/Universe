#pragma once
#include <windows.h>
#include <memory.h> 

#include"dx_11.h"
#include"camera.h"
#include"geometry.h"
#include"lighting.h"
#include"math_3d.h"

class Engine
{
	std::unique_ptr<DX_11> device;
	shared_ptr<Geometry::Geometry> geometry;
	shared_ptr<Camera> camera;
	shared_ptr<Light> light;

	thread render_thread;

	HWND hWnd;

	int render_ctrl;

public:
	void start_render();
	void stop_render();
	void exit_render();

	Engine(HWND _hWnd);
	~Engine();

	bool init();
	void render();

	// Camera
	void moveCamera(int x, int y);
	void resize();
};