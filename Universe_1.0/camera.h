#pragma once

#include <windows.h>
#include <xnamath.h>

#include <thread>
#include <mutex>

#include "math_3d.h"

struct cameraDef
{
	Math_3d::Vector_4d a;
	Math_3d::Vector_4d b;
	Math_3d::Vector_4d c;
	Math_3d::Vector_4d d;
	Math_3d::Vector_4d color = { 0.0f, 0.0f, 0.0f, 0.0f};
};

class Camera
{

	XMVECTOR eye;
	XMVECTOR at;
	XMVECTOR up;

	Math_3d::Vector_3d pos;
	Math_3d::Vector_3d viewPoint;

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