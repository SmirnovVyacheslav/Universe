#include"engine.h"

extern int wnd_width;
extern int wnd_height;

Engine::Engine(HWND _hWnd) : hWnd(_hWnd)
{
	render_ctrl = 0;
}

bool Engine::init() 
{
	device.reset(new DX_11(hWnd));
	if (!device->init())
		return false;

	camera.reset(new Camera(wnd_width, wnd_height));
	device->setCamera(camera);

	geometry.reset(new Geometry::Geometry());
	device->setGeometry(geometry);

	light.reset(new Light(geometry, camera));

	render_ctrl = 0;

	render_thread = thread(&Engine::render, this);

	return true;
}

Engine::~Engine()
{

}

void Engine::start_render()
{
	render_ctrl = 1;
}

void Engine::stop_render()
{
	render_ctrl = 0;
}

void Engine::exit_render()
{
	render_ctrl = -1;
	render_thread.join();
}

void Engine::render()
{
	while (render_ctrl != -1)
	{
		if (render_ctrl)
		{
			device->updateGeometry();
			device->render();
		}
	}
}

void Engine::moveCamera(int x, int y)
{
	camera->move(x, y);
}

void Engine::resize()
{

}