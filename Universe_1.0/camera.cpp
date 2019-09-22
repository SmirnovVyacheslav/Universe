#include"camera.h"

Camera::Camera(int wndWidth, int wndHeight)
{
	eye = XMVectorSet(10.0f, 10.0f, -10.0f, 0.0f);
	at = XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	pos = Vector3(0.0f, 1.0f, -1.0f);

	camera_def.a = { 0.0f, 0.0f, 0.0f, 0.0f };
	camera_def.b = { 0.0f, 0.0f, 0.0f, 0.0f };
	camera_def.c = { 0.0f, 0.0f, 0.0f, 0.0f };
	camera_def.d = { 0.0f, 0.0f, 0.0f, 0.0f };

	viewPoint = { 0.0f, 0.0f, 0.0f };

	_view = XMMatrixLookAtLH(eye, at, up);
	_projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)wndWidth / (FLOAT)wndHeight, 0.01f, 100.0f);
}

XMMATRIX Camera::view()
{
	camera_mutex.lock();
	XMMATRIX tmp_view = _view;
	camera_mutex.unlock();
	return tmp_view;
}

XMMATRIX& Camera::projection()
{
	return _projection;
}

void Camera::move(int _x, int _y)
{
	int xDiff = _x;
	int yDiff = _y;

	xAngle += static_cast<float>(xDiff) * sensitivity;
	yAngle += static_cast<float>(yDiff) * sensitivity;

	if (yAngle > 89.0f)
		yAngle = 89.0f;
	if (yAngle < -89.0f)
		yAngle = -89.0f;

	float xAngleRad = xAngle * XM_PI / 180.0f;
	float yAngleRad = yAngle * XM_PI / 180.0f;

	float vx = cos(xAngleRad) * cos(yAngleRad);
	float vy = sin(yAngleRad);
	float vz = sin(xAngleRad) * cos(yAngleRad);

	eye = XMVectorSet(vx * radius, vy * radius, vz * radius, 0.0f);

	camera_mutex.lock();
	_view = XMMatrixLookAtLH(eye, at, up);
	camera_mutex.unlock();

	pos = Vector3(vx * radius, vy * radius, vz * radius);


	camera_def.a = { 0.0f, 0.0f, 0.0f, 0.0f };
	camera_def.b = { 0.0f, 0.0f, 0.0f, 0.0f };
	camera_def.c = { 0.0f, 0.0f, 0.0f, 0.0f };
	camera_def.d = { 0.0f, 0.0f, 0.0f, 0.0f };

	viewPoint = { 0.0f, 0.0f, 0.0f };
}

cameraDef& Camera::get_def()
{
	return camera_def;
}