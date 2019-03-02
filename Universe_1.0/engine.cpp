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

	return true;
}

void Engine::render()
{
	light->startTracing();

	device->updateGeometry();
	device->render();
}

void Engine::moveCamera(int x, int y)
{
	camera->move(x, y);
}

void Engine::resize()
{
	camera->resize();
}