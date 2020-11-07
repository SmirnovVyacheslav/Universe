/******************************************************************************
	 * File: geometry.cpp
	 * Description: Contains geometry building.
	 * Created: 09 Aug 2020
	 * Copyright: (C) 2020 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com

******************************************************************************/

#include "geometry.h"

namespace Geometry
{
	int Object::obj_counter = 0;
	std::vector<Object*> objects;

	Shape::Shape(std::string type, bool wrap)
	: wrap(wrap)
	{
		if (type == "square")
		{
			data = { std::make_pair(1.0f, 0.0f),
					 std::make_pair(1.0f, 90.0f),
					 std::make_pair(1.0f, 180.0f),
					 std::make_pair(1.0f, 270.0f) };
		}
	}

	std::vector<std::pair<float, float>>::iterator Shape::begin()
	{
		return data.begin();
	}
	std::vector<std::pair<float, float>>::iterator Shape::end()
	{
		return data.end();
	}
	std::vector<std::pair<float, float>>::const_iterator Shape::begin() const
	{
		return data.cbegin();
	}
	std::vector<std::pair<float, float>>::const_iterator Shape::end() const
	{
		return data.cend();
	}

	int Shape::size() const
	{
		return data.size();
	}

	int Shape::get_edges_number() const
	{
		return wrap ? data.size() : data.size() - 1;
	}

	Path::Path(std::vector<Math_3d::Vector_3d> control_points)
	: control_points(control_points) {}

	Math_3d::Vector_3d Path::get_point(float t) const
	{
		Math_3d::Vector_3d result;
		int n = control_points.size() - 1;

		for (int i = 0; i < control_points.size(); ++i)
		{
			float binom_factorial = Math_3d::factorial(n) / (Math_3d::factorial(i) * Math_3d::factorial(n - i));
			float bernstein_polynom = binom_factorial * pow(t, i) * pow(1.0f - t, n - i);

			result += control_points[i] * bernstein_polynom;
		}

		return result;
	}

	Generator::Generator() {}

	Generator::Generator(std::unique_ptr<Path> path, std::unique_ptr<Shape> shape, Math_3d::Vector_3d base_vec)
	: path(std::move(path)), shape(std::move(shape)), base_vec(base_vec) {}

	void Generator::make_mesh(Object_Data& data)
	{
		int object_first_index = data.vertices.size();

		// Go through slices and apply shape to them
		for (float t = 0.0f; t < 1.0f; t += step)
		{
			int start_index = data.vertices.size();
			Math_3d::Vector_3d center = path->get_point(t);

			Math_3d::Vector_3d path_vec = (path->get_point(t + path_delta) - center).normalize();
			base_vec = Math_3d::project_vector_to_plane(base_vec, center, path_vec).normalize();
			for (auto item : *shape)
			{
				Vertex vertex;
				const float length = item.first;
				const float angle = item.second;

				vertex.pos = center + (Math_3d::rotate_vector(base_vec, path_vec, angle).normalize() * length);
				data.vertices.push_back(vertex);
			}

			// Set indices, not required for first
			if (t > path_delta)
			{
				for (int i = 0; i < shape->get_edges_number(); ++i)
				{
					int p1_index = start_index - shape->size() + i;
					int p2_index = start_index - shape->size() + (i + 1) % shape->size();
					int p3_index = start_index + (i + 1) % shape->size();
					int p4_index = start_index + i;

					data.indices.push_back(p1_index);
					data.indices.push_back(p2_index);
					data.indices.push_back(p3_index);

					data.indices.push_back(p1_index);
					data.indices.push_back(p3_index);
					data.indices.push_back(p4_index);
				}
			}
		}
		int object_last_index = data.vertices.size();

		if (!solid)
		{
			return;
		}

		Vertex vertex;
		// Begin center vertex
		vertex.pos = path->get_point(0.0);
		data.vertices.push_back(vertex);
		// End center vertex
		vertex.pos = path->get_point(1.0);
		data.vertices.push_back(vertex);

		// Add mesh for begin sector
		make_solid(data, object_first_index, object_last_index);
		// Add mesh for end sector
		make_solid(data, object_last_index - shape->size(), object_last_index + 1);

		data.size = data.indices.size();
	}

	void Generator::make_solid(Object_Data& data, int start_index, int center_index)
	{
		for (int i = 0; i < shape->size(); ++i)
		{
			int a_index = start_index + i;
			int b_index = start_index + (i + 1) % shape->size();
			int c_index = center_index;

			Math_3d::Vector_3d ab_vec = data.vertices[b_index].pos - data.vertices[a_index].pos;
			Math_3d::Vector_3d bc_vec = data.vertices[c_index].pos - data.vertices[b_index].pos;
			Math_3d::Vector_3d ac_vec = data.vertices[c_index].pos - data.vertices[a_index].pos;

			// A * * B
			//  * * *
			//   * *
			//    C
			// Loop via level
			// Add vertex
			int start_index = data.vertices.size();
			for (int j = 0; j < split_points + 2; ++j)
			{
				Math_3d::Vector_3d start_point = data.vertices[a_index].pos + ac_vec * sector_step * j;
				// Loop via row
				for (int k = 0; k < split_points + 2 - j; k++)
				{
					Math_3d::Vector_3d new_point = start_point + ab_vec * sector_step * k;
					if (new_point != data.vertices[a_index].pos && new_point != data.vertices[b_index].pos && new_point != data.vertices[c_index].pos)
					{
						Vertex new_vertex;
						new_vertex.pos = new_point;
						data.vertices.push_back(new_vertex);
					}
				}
			}

			// Add indexies
			int sub_row_index_start = 0;
			for (int j = 0; j < split_points + 1; ++j)
			{
				for (int k = 0; k < (split_points * 2) + 1 - j * 2; ++k)
				{
					// Add low triangle
					// 1   2
					//   3
					if (k % 2)
					{
						int p1_index = start_index + sub_row_index_start + (k / 2);
						int p2_index = start_index + sub_row_index_start + (k / 2) + 1;
						int p3_index = start_index + sub_row_index_start + (split_points + 2 - j) + (k / 2);

						data.indices.push_back(p1_index);
						data.indices.push_back(p2_index);
						data.indices.push_back(p3_index);
					}
					// Add high triangle
					//   1
					// 2   3
					else
					{
						int p1_index = start_index + sub_row_index_start + (k / 2) + 1;
						int p2_index = start_index + sub_row_index_start + (split_points + 2 - j) + (k / 2);
						int p3_index = start_index + sub_row_index_start + (split_points + 2 - j) + (k / 2) + 1;

						data.indices.push_back(p1_index);
						data.indices.push_back(p2_index);
						data.indices.push_back(p3_index);
					}

				}
				sub_row_index_start += split_points + 2 - j;
			}
		}
	}

	//Vector3 GeometryConstructor::get_value_default(int i, int j)
	//{
	//	return u_step * i + v_step * j;
	//}

	//Vector3 GeometryConstructor::get_value(int i, int j)
	//{
	//	if (i > 0 && j > 0 && i < u_square && j < v_square)
	//	{
	//		float y = interval / float(RAND_MAX) * float(rand());
	//		return u_step * i + v_step * j + Vector3(0.0f, y, 0.0f);
	//	}
	//	return get_value_default(i, j);
	//}


	//Vector3 GeometryConstructor::get_normal(Edge edge, Vector3 vertex)
	//{
	//	normal = (vertex - back_vertex).normalize();
	//	if (edge.a == edge.b || edge.a == edge.c || edge.b == edge.c)
	//	{
	//		return normal;
	//	}
	//	return ((edge.a - edge.b) ^ (edge.a - edge.c)).normalize();
	//}

	//bool GeometryConstructor::check_index(int index, int max)
	//{
	//	if (index < 0)
	//	{
	//		return false;
	//	}
	//	if (index >= max)
	//	{
	//		return false;
	//	}
	//	return true;
	//}

	//void GeometryConstructor::calc_normal(Vertex* data)
	//{
	//	for (int j = 0; j < v_vertex; ++j)
	//	{
	//		for (int i = 0; i < u_vertex; ++i)
	//		{
	//			vector<Edge> near_egdes;
	//			Vector3 vertex_normal = { 0.0f, 0.0f, 0.0f };

	//			// check t1 & t2
	//			if (check_index(j - 1, v_vertex) && check_index(i - 1, u_vertex))
	//			{
	//				//t1
	//				near_egdes.push_back({
	//					data[(j - 1) * u_vertex + i - 1].pos,
	//					data[j * u_vertex + i].pos,
	//					data[j * u_vertex + i - 1].pos
	//					});
	//				//t2
	//				near_egdes.push_back({
	//					data[(j - 1) * u_vertex + i - 1].pos,
	//					data[(j - 1) * u_vertex + i].pos,
	//					data[j * u_vertex + i].pos
	//					});
	//			}
	//			// check t3
	//			if (check_index(j - 1, v_vertex) && check_index(i + 1, u_vertex))
	//			{
	//				//t3
	//				near_egdes.push_back({
	//					data[(j - 1) * u_vertex + i].pos,
	//					data[j * u_vertex + i + 1].pos,
	//					data[j * u_vertex + i].pos
	//					});
	//			}
	//			// check t4 & t5
	//			if (check_index(j + 1, v_vertex) && check_index(i + 1, u_vertex))
	//			{
	//				//t4
	//				near_egdes.push_back({
	//					data[j * u_vertex + i].pos,
	//					data[j * u_vertex + i + 1].pos,
	//					data[(j + 1) * u_vertex + i + 1].pos
	//					});

	//				//t5
	//				near_egdes.push_back({
	//					data[j * u_vertex + i].pos,
	//					data[(j + 1) * u_vertex + i + 1].pos,
	//					data[(j + 1) * u_vertex + i].pos
	//					});
	//			}
	//			// check t6
	//			if (check_index(j + 1, v_vertex) && check_index(i - 1, u_vertex))
	//			{
	//				near_egdes.push_back({
	//					data[j * u_vertex + i - 1].pos,
	//					data[j * u_vertex + i].pos,
	//					data[(j + 1) * u_vertex + i].pos
	//					});
	//			}

	//			for (auto edge : near_egdes)
	//			{
	//				vertex_normal = vertex_normal + get_normal(edge, data[j * u_vertex + i].pos);
	//			}
	//			vertex_normal = (vertex_normal / near_egdes.size()).normalize();

	//			if (rad_to_deg(angle(vertex_normal, normal)) > 90.0f)
	//			{
	//				vertex_normal = vertex_normal * -1.0f;
	//			}

	//			data[j * u_vertex + i].normal = vertex_normal;
	//		}
	//	}
	//}

	//void GeometryConstructor::make_plane(ObjectData& data)
	//{
	//	int start_index = data.vertices.size();
	//	data.vertices.resize(data.vertices.size() + u_vertex * v_vertex);
	//	Vertex* vertex_data = &data.vertices[start_index];
	//	int p1_index, p2_index, p3_index, p4_index;
	//	for (int j = 0; j < v_square; ++j)
	//	{
	//		for (int i = 0; i < u_square; ++i)
	//		{
	//			if (wrap)
	//			{
	//				p1_index = j * u_vertex + i;
	//				p2_index = j * u_vertex + (i + 1) % u_vertex;
	//				p3_index = (j + 1) * u_vertex + (i + 1) % u_vertex;
	//				p4_index = (j + 1) * u_vertex + i;
	//			}
	//			else
	//			{
	//				p1_index = j * u_vertex + i;
	//				p2_index = j * u_vertex + i + 1;
	//				p3_index = (j + 1) * u_vertex + i + 1;
	//				p4_index = (j + 1) * u_vertex + i;
	//			}

	//			vertex_data[p1_index].pos = pos + get_value(i, j);
	//			vertex_data[p2_index].pos = pos + get_value(i + 1, j);
	//			vertex_data[p3_index].pos = pos + get_value(i + 1, j + 1);
	//			vertex_data[p4_index].pos = pos + get_value(i, j + 1);

	//			data.indices.push_back(start_index + p1_index);
	//			data.indices.push_back(start_index + p2_index);
	//			data.indices.push_back(start_index + p3_index);

	//			data.indices.push_back(start_index + p1_index);
	//			data.indices.push_back(start_index + p3_index);
	//			data.indices.push_back(start_index + p4_index);
	//		}
	//	}

	//	data.size = data.indices.size();

	//	//Calc normales
	//	calc_normal(vertex_data);
	//}

	//void GeometryConstructor::make_triangle(ObjectData& data, Edge edge)
	//{
	//	int start_index = data.vertices.size();
	//	data.vertices.push_back(Vertex{ edge.a, get_normal(edge, edge.a) });
	//	data.vertices.push_back(Vertex{ edge.b, get_normal(edge, edge.b) });
	//	data.vertices.push_back(Vertex{ edge.c, get_normal(edge, edge.c) });

	//	data.indices.push_back(start_index);
	//	data.indices.push_back(start_index + 1);
	//	data.indices.push_back(start_index + 2);
	//}



	Geometry::Geometry()
	{
		//person = new Person();

		/*landscape = new Landscape();
		landscape->create();
		scene.push_back(landscape);*/

		/*Object* test = new Test;
		test->create();
		scene.push_back(test);*/
	}

	Geometry::~Geometry()
	{
		for (auto obj : scene)
		{
			delete obj;
		}
	}

	std::vector<Object*>::iterator Geometry::begin()
	{
		return objects.begin();
	}

	std::vector<Object*>::iterator Geometry::end()
	{
		return objects.end();
	}


	Person::Person(Object* base) : Object(base) {}

	Person::~Person()
	{
		for (auto obj : components)
		{
			delete obj;
		}
	}

	void Person::create()
	{

	}


	Landscape::Landscape(Object* base) : Object(base)
	{
		data = new Object_Data;
		objects.push_back(this);
	}

	Landscape::~Landscape()
	{
		delete data;

		for (auto obj : components)
		{
			delete obj;
		}
	}

	void Landscape::create()
	{
		/*GeometryConstructor construstor;

		construstor.make_plane(*data);

		data->color = { 1.0f, 1.0f, 0.0f };*/
	}


	Test::Test(Object* _base) : Object(_base)
	{
		data = new Object_Data;
		objects.push_back(this);
	}

	Test::~Test()
	{
		delete data;
	}

	void Test::create()
	{
		/*vector<Vector3> control_points = { Vector3(1.0f, -5.0f, -1.0f), Vector3(1.0f, 2.0f, -1.0f), Vector3(1.0f, 3.0f, -1.0f) };
		Vector3 base_vec = Vector3(1.0f, 0.0f, 0.0f);
		GeometryConstructor construstor(std::make_unique<GeometryPath>(control_points),
			std::make_unique<GeometryShape>(), base_vec);

		construstor.make_mesh(*data);

		data->color = { 0.0f, 0.0f, 1.0f };*/
	}



	Object::Object(Object* _base) : base(_base)
	{
		data = nullptr;
		id = obj_counter++;

		pos = { 0.0f, 0.0f, 0.0f };
	}

	Object::~Object() {}

	int Object::get_id()
	{
		return id;
	}

	Object_Data* Object::get_data()
	{
		return data;
	}


	void Object::move_down()
	{
		if (data != nullptr)
		{
			for (Vertex& vertex : data->vertices)
			{
				vertex.pos.y -= 10.0f;
			}
		}
		else
		{
			for (auto obj : components)
			{
				obj->move_down();
			}
		}
	}
}
