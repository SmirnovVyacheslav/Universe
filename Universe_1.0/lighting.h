#pragma once
#include <vector>
#include <memory>

#include "geometry.h"
#include "dx_11.h"
#include "x_vector.h"

class Camera;

class Light
{
	float intensity; //intensity

	Vector3 lightPos;
	Vector4 lightColor;

	int depth;

	std::shared_ptr<Geometry> geometry;
	std::shared_ptr<Camera>   camera;

public:
	Light(std::shared_ptr<Geometry> _geometry, std::shared_ptr<Camera> _camera);

	void startTracing();

	void process(Vector3 lightPos, Vector4 lightColor, Object &obj, Vertex &vertex, float intensity, int depth);
};