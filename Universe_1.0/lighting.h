#pragma once
#include <vector>
#include <memory>

#include "geometry.h"
#include "dx_11.h"

//struct material
//{
//	float diffuse = 0.7f;
//	float mirror = 0.3f;
//};

class Camera;

class Light
{
	float intensity; //intensity

	XMFLOAT4 LightPos;
	XMFLOAT4 LightColor;

	int depth;

	std::shared_ptr<Geometry> geometry;
	std::shared_ptr<Camera> camera;

public:
	Light();

	void start_tracing(std::shared_ptr<Geometry> _geometry, std::shared_ptr<Camera> _camera);

	void process(XMFLOAT4 light_pos, Object &obj, Vertex &vertex, float intensity, int depth);

	void reset_color();

	float point_dest(XMFLOAT3 p1, XMFLOAT3 p2);
};