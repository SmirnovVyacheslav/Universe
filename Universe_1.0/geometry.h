/******************************************************************************
	 * File: geometry.h
	 * Description: Contains geometry building.
	 * Created: 09 Aug 2020
	 * Copyright: (C) 2020 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com

******************************************************************************/

#include <vector>
#include <Windows.h>

//#include <xnamath.h>
#include <mutex>
#include <memory>
#include <map>

#include "math_3d.h"

namespace geometry
{
	//using std::vector;
	//using std::wstring;
	//using std::mutex;
	//using std::map;
	//using std::unique_ptr;
	//using std::shared_ptr;
	//using std::string;

	class Object;
	struct ObjectData;

	// Bezier curve
	class GeometryPath
	{

	public:
		vector<Vector3> control_points;

		GeometryPath(vector<Vector3> control_points);

		Vector3 get_point(float t);

		float calc_point(int index);

		float factorial(int n);
	};

	struct Vertex
	{
		Vector3 pos;
		Vector3 normal;
		//Vector4 color;
	};

	struct ObjectData
	{
		int            size;
		vector<DWORD>  indices;
		vector<Vertex> vertices;
		Vector3 color;
	};


	struct Shape
	{
		float len;
		float angle;

		Shape(float _len, float _angle);
	};

	struct GeometryShape
	{
		vector<Shape> data;

		GeometryShape();
	};


	class GeometryConstructor
	{
		std::unique_ptr<GeometryPath> path;
		std::unique_ptr<GeometryShape> shape;
		Vector3 base_vec; // should be normalized

		float step = 0.02f;
		float eps = 0.001f;
		bool wrap = true;
		bool solid = true;

		//temp
		struct Edge
		{
			Vector3 a;
			Vector3 b;
			Vector3 c;
		};

		unsigned rand_value = 11;
		float interval = 1.0f;
		Vector3 pos = { -50.0f, -10.0f, 50.0f };
		Vector3 normal;

		Vector3 u_vec = { 1.0f, 0.0f, 0.0f };
		Vector3 v_vec = { 0.0f, 0.0f, -1.0f };
		Vector3 back_vertex = { 0.0f, -20.0f, 0.0f };

		int u_square = static_cast<int>(50); // TODO make resolution calc
		int v_square = static_cast<int>(50);
		int w_square = static_cast<int>(50);
		int u_vertex = u_square + 1;
		int v_vertex = v_square + 1;

		Vector3 u_step = u_vec * (200.0f / float(u_square));
		Vector3 v_step = v_vec * (200.0f / float(v_square));

		float teta = 2.0f * pi / (float)u_square;
		float psy = 2.0f * pi / (float)u_square;
		float w_step = 0.0f / (float)w_square;
		//temp

	public:
		GeometryConstructor();
		GeometryConstructor(std::unique_ptr<GeometryPath> _path,
			std::unique_ptr<GeometryShape> _shape, Vector3 _base_vec);

		~GeometryConstructor() {};

		void make_mesh(ObjectData& data);
		// TODO remake
		void make_plane(ObjectData& data);
		Vector3 get_normal(Edge edge, Vector3 vertex);
		bool check_index(int index, int max);
		void calc_normal(Vertex* data);
		Vector3 get_value(int i, int j);
		Vector3 get_value_default(int i, int j);
		void make_triangle(ObjectData& data, Edge edge);
		// TODO remake

		Vector3 rotate(Vector3 vec, Vector3 axis, float angle);

		Vector3 make_projection(Vector3 vec, Vector3 point_a, Vector3 normal);
	};


	class Object
	{
	protected:
		int id;
		static int obj_counter;

		Object* base;
		ObjectData* data;
		vector<Object*> components;

		Vector3 pos;

	public:

		Object(Object* base);
		virtual ~Object();

		virtual void create() = 0;

		int get_id();

		ObjectData* get_data();

		void move_down();

	};

	class Geometry
	{
		// Object* person;
		Object* landscape;

		vector<Object*> scene;

	public:
		Geometry();
		~Geometry();

		vector<Object*>::iterator begin();
		vector<Object*>::iterator end();
	};

	class Person : public Object
	{
	public:
		Person(Object* base = nullptr);
		~Person();

		virtual void create();
	};

	class Landscape : public Object
	{
	public:
		Landscape(Object* base = nullptr);
		~Landscape();

		virtual void create();
	};

	class Test : public Object
	{
	public:
		Test(Object* base = nullptr);
		~Test();

		virtual void create();
	};
}
