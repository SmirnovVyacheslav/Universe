/******************************************************************************
	 * File: geometry.h
	 * Description: Contains geometry building.
	 * Created: 09 Aug 2020
	 * Copyright: (C) 2020 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com

******************************************************************************/

// #include <vector>
// #include <Windows.h>

// //#include <xnamath.h>
// #include <mutex>
// #include <memory>
// #include <map>

#include "math_3d.h"

namespace Geometry
{
	/**
	* @struct Vertex
	* Base struct which represents single vertex
	*/
	struct Vertex
	{
		Math_3d::Vector_3d pos;
		Math_3d::Vector_3d normal;
	};

	/**
	* @struct object_data
	* Base struct which represents single object data
	* Contains vector of vertices and indices
	*/
	struct Object_Data
	{
		int            size;
		// vector<DWORD>  indices;
		std::vector<unsigned long int>  indices;
		std::vector<Vertex> vertices;
		Math_3d::Vector_3d color;
	};


	/**
	* @class Shape
	* 3D shape which represents object slice.
	* Idea is - have some start point, vector and
	* have a vector of {length, angle} for each point
	* It means that need to go from start point to
	* vector * length rotated to angle
	*/
	class Shape
	{
		using std::vector<std::tuple<float, float>> data_type;

		bool wrap = true;
		/**
		 * Shape point data:
		 *  - Length
		 *  - Angle
		 */
		data_type data;

	public:
		Shape(std::string type, bool wrap);

		data_type::iterator begin();
		data_type::iterator end();
		data_type::const_iterator begin() const;
		data_type::const_iterator end() const;

		int size() const;
		int get_edges_number() const;
	};

	/**
	* @class Path
	* 3D Path which represents object path.
	* Implemented as Bezier curve of given
	* control points.
	*/
	class Path
	{
		std::vector<Math_3d::Vector_3d> control_points;

	public:

		Path(std::vector<Math_3d::Vector_3d> control_points);

		Math_3d::Vector_3d get_point(float t) const;
	};

	/**
	* @class Generator
	* 3D geometry objects generator.
	*/
	class Generator
	{
		std::unique_ptr<Path> path;
		std::unique_ptr<Shape> shape;
		Math_3d::Vector_3d base_vec;

		const float step = 0.02f;
		const float path_delta = 0.01f;
		bool solid = true;
		int split_points = 3;

	public:
		Generator();
		Generator(std::unique_ptr<Path> path, std::unique_ptr<Shape> shape, Math_3d::Vector_3d base_vec);

		~Generator() {};

		void make_mesh(Object_Data& data);


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
	}

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
