#pragma once
#include <vector>
#include <memory>
#include <thread>

#include <queue>

#include "geometry.h"
#include "dx_11.h"
#include "math_3d.h"

using std::thread;
using std::vector;

class Camera;

class Light
{
	float intensity; //intensity

	Math_3d::Vector_3d lightPos;
	Math_3d::Vector_4d lightColor;

	int depth;

	std::shared_ptr<Geometry::Geometry> geometry;
	std::shared_ptr<Camera>   camera;

public:
	Light(std::shared_ptr<Geometry::Geometry> _geometry, std::shared_ptr<Camera> _camera);
	~Light();
};