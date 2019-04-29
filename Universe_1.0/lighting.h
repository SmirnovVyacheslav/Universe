#pragma once
#include <vector>
#include <memory>
#include <thread>

#include <queue>

#include "geometry.h"
#include "dx_11.h"
#include "x_vector.h"

using std::thread;
using std::vector;

class Camera;

class Light
{
	struct light_data
	{
		Vector3 src;
		Vector4 color;
		Object* obj;
		float intensity;

		light_data(Vector3 src, Vector4 color, Object* obj, float intensity) : src(src), color(color), obj(obj), intensity(intensity) {};
		light_data() {};
	};

	float intensity; //intensity

	Vector3 lightPos;
	Vector4 lightColor;

	int depth;

	std::shared_ptr<Geometry> geometry;
	std::shared_ptr<Camera>   camera;

	//vector<thread> pool;
	//thread trace_thr;
	//thread shade_thr;

	vector<light_data> data;
	vector<light_data> new_data;

	/*void trace();
	void shade();
	int thread_ctrl;*/
	
	/*std::queue<bool> shade_data;
	std::mutex start_trace;
	std::mutex start_shade;*/

public:
	Light(std::shared_ptr<Geometry> _geometry, std::shared_ptr<Camera> _camera);
	~Light();

	void startTracing();

	//void trace(Object *obj);

	//void process(Vector3 lightPos, Vector4 lightColor, Object &obj, Vertex &vertex, float intensity, int depth);
	void process(Vector3 lightPos, Vector4 lightColor, Object &obj, Vertex &vertex, float intensity, int depth, map<Vertex*, int> &modVertex);
};