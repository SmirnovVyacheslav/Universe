#include"engine.h"

Engine::Engine(HWND _hWnd) : hWnd(_hWnd)
{

}

bool Engine::init() 
{
	device.reset(new DX_11(hWnd));
	if (!device->createDevice())
		return false;

	camera.reset(new Camera(hWnd));
	device->setCamera(camera);

	geometry.reset(new Geometry());
	device->setGeometry(geometry);

	light.reset(new Light(geometry, camera));

	render_ctrl = 0;

	render_thread = thread(&Engine::render, this);
	render_thread.detach();

	return true;
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
}

void Engine::render()
{
	while (render_ctrl != -1)
	{
		if (render_ctrl)
		{
			light->startTracing();

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
	camera->resize();
}