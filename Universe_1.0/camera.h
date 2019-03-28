#pragma once

#include <windows.h>
#include <xnamath.h>

#include <thread>
#include <mutex>

#include "x_vector.h"

class Camera
{

	XMVECTOR eye;
	XMVECTOR at;
	XMVECTOR up;

	Vector3 pos;
	Vector3 viewPoint;

	XMMATRIX _view;
	XMMATRIX _projection;

	float xAngle = 0.0f;
	float yAngle = -90.0f;
	float radius = 3.0f;
	float sensitivity = 0.1f;

	HWND hWnd;
	int wndWidth, wndHeight, wndX, wndY;
	int topBorder, leftBorder;

	XMMATRIX xRot;
	XMMATRIX yRot;
	XMMATRIX zRot;

	int x = 0;
	int y = 0;

	std::mutex camera_mutex;

public:

	Camera(HWND _hWnd);

	//XMMATRIX& view();
	XMMATRIX view();

	XMMATRIX& projection();

	void move(int x, int y);

	void resize();

	bool cameraCross(Vector3 srcPos, Vector3 dstPos);
};