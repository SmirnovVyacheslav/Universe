#pragma once

#include <windows.h>
#include <xnamath.h>

#include <thread>
#include <mutex>

#include "x_vector.h"

struct cameraDef
{
	Vector4 a;
	Vector4 b;
	Vector4 c;
	Vector4 d;
	Vector4 color = { 0.0f, 0.0f, 0.0f, 0.0f};
};

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
	float radius = 6.0f;
	float sensitivity = 0.1f;

	std::mutex camera_mutex;

	cameraDef camera_def;

public:

	Camera(int wndWidth, int wndHeight);

	XMMATRIX view();

	XMMATRIX& projection();

	void move(int x, int y);

	cameraDef& get_def();
};