/******************************************************************************
	 * File: math_3d.cpp
	 * Description: Contains utility classes and functions for 3D.
	 * Created: 09 Aug 2020
	 * Copyright: (C) 2020 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com

******************************************************************************/

#include "math_3d.h"

namespace Math_3d
{
	float factorial(int n)
	{
		if (n == 0 || n == 1)
			return 1.0f;

		float result = 1.0f;
		for (int i = 1; i <= n; ++i)
		{
			result *= static_cast<float>(i);
		}
		return result;
	}

	float radian_to_degree(float radian)
	{
		return radian * 180.0f / pi;
	}

	float degree_to_radian(float degree)
	{
		return degree * pi / 180.0f;
	}

	Vector_3d project_vector_to_plane(Vector_3d vector_to_project, Vector_3d plane_point, Vector_3d plane_normal)
	{
		// Need to make projection only for vector_end_point
		Vector_3d vector_end_point = vector_to_project + plane_point;

		// Make dot projection
		float distance_to_plane = vector_to_project & plane_normal;
		Vector_3d plane_point_b = vector_end_point - (distance_to_plane * plane_normal);

		// Construst new projection for vector
		return plane_point_b - plane_point;
	}

	Vector_3d rotate_vector(Vector_3d vector, Vector_3d axis, float angle)
	{
		angle = degree_to_radian(angle);
		// Rotation matrix
		std::vector<Vector_3d> matrix = {
			Vector_3d(cos(angle) + (1 - cos(angle)) * axis.x * axis.x,
					 (1 - cos(angle)) * axis.x * axis.y - sin(angle) * axis.z,
					 (1 - cos(angle)) * axis.x * axis.z + sin(angle) * axis.y),
			Vector_3d((1 - cos(angle)) * axis.x * axis.y + sin(angle) * axis.z,
					 cos(angle) + (1 - cos(angle)) * axis.y * axis.y,
					 (1 - cos(angle)) * axis.y * axis.z - sin(angle) * axis.x),
			Vector_3d((1 - cos(angle)) * axis.x * axis.z - sin(angle) * axis.y,
					 (1 - cos(angle)) * axis.y * axis.z + sin(angle) * axis.x,
					 cos(angle) + (1 - cos(angle)) * axis.z * axis.z)
		};

		Vector_3d result = {
			matrix[0] & vector,
			matrix[1] & vector,
			matrix[2] & vector
		};

		return result;
	}

	bool Vector_3d::is_zero()
	{
		return (x + y + z) < eps;
	}

	float Vector_3d::length()
	{
		double _x = static_cast<double>(x);
		double _y = static_cast<double>(y);
		double _z = static_cast<double>(z);
		return static_cast<float>(sqrt(_x * _x + _y * _y + _z * _z));
	}

	Vector_3d& Vector_3d::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}

	Vector_3d& Vector_3d::trunc()
	{
		x = x > 1.0f ? 1.0f : x;
		y = y > 1.0f ? 1.0f : y;
		z = z > 1.0f ? 1.0f : z;
		return *this;
	}

	Vector_3d& Vector_3d::operator=(const Vector_3d& vec)
	{
		if (this != &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		return *this;
	}

	Vector_3d& Vector_3d::operator+=(const float& num)
	{
		x += num; y += num; z += num;
		return *this;
	}
	Vector_3d& Vector_3d::operator-=(const float& num)
	{
		x -= num; y -= num; z -= num;
		return *this;
	}
	Vector_3d& Vector_3d::operator*=(const float& num)
	{
		x *= num; y *= num; z *= num;
		return *this;
	}
	Vector_3d& Vector_3d::operator/=(const float& num)
	{
		x /= num; y /= num; z /= num;
		return *this;
	}
	Vector_3d& Vector_3d::operator+=(const Vector_3d& vec)
	{
		x += vec.x; y += vec.y; z += vec.z;
		return *this;
	}
	Vector_3d& Vector_3d::operator-=(const Vector_3d& vec)
	{
		x -= vec.x; y -= vec.y; z -= vec.z;
		return *this;
	}
	Vector_3d& Vector_3d::operator*=(const Vector_3d& vec)
	{
		x *= vec.x; y *= vec.y; z *= vec.z;
		return *this;
	}
	Vector_3d& Vector_3d::operator/=(const Vector_3d& vec)
	{
		x /= vec.x; y /= vec.y; z /= vec.z;
		return *this;
	}

	/**
	 * Scalar cross product
	 */
	float Vector_3d::operator&=(const Vector_3d& vec)
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	/**
	 * Vector cross product
	 */
	Vector_3d& Vector_3d::operator^=(const Vector_3d& vec)
	{
		x = y * vec.z - z * vec.y;
		y = z * vec.x - x * vec.z;
		z = x * vec.y - y * vec.x;
		return *this;
	}

	Vector_3d::operator Vector_4d()
	{
		return { x, y, z, 1.0f };
	}

	Vector_3d operator+(const Vector_3d& vec_a, const Vector_3d& vec_b)
	{
		return { vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z };
	}
	Vector_3d operator-(const Vector_3d& vec_a, const Vector_3d& vec_b)
	{
		return { vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z };
	}
	Vector_3d operator*(const Vector_3d& vec_a, const Vector_3d& vec_b)
	{
		return { vec_a.x * vec_b.x, vec_a.y * vec_b.y, vec_a.z * vec_b.z };
	}
	Vector_3d operator/(const Vector_3d& vec_a, const Vector_3d& vec_b)
	{
		return { vec_a.x / vec_b.x, vec_a.y / vec_b.y, vec_a.z / vec_b.z };
	}
	/**
	 * Scalar cross product
	 */
	float operator&(const Vector_3d& vec_a, const Vector_3d& vec_b)
	{
		return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
	}
	/**
	 * Vector cross product
	 */
	Vector_3d operator^(const Vector_3d& vec_a, const Vector_3d& vec_b)
	{
		return { vec_a.y * vec_b.z - vec_a.z * vec_b.y,
				 vec_a.z * vec_b.x - vec_a.x * vec_b.z,
				 vec_a.x * vec_b.y - vec_a.y * vec_b.x };
	}

	bool operator==(const Vector_3d& vec_a, const Vector_3d& vec_b)
	{
		if ((vec_a.x - vec_b.x) * (vec_a.x - vec_b.x) > eps)
			return false;

		if ((vec_a.y - vec_b.y) * (vec_a.y - vec_b.y) > eps)
			return false;

		if ((vec_a.z - vec_b.z) * (vec_a.z - vec_b.z) > eps)
			return false;

		return true;
	}
	bool operator!=(const Vector_3d& vec_a, const Vector_3d& vec_b)
	{
		return !(vec_a == vec_b);
	}

	Vector_3d operator+(const float& num, const Vector_3d& vec)
	{
		return { num + vec.x, num + vec.y, num + vec.z };
	}
	Vector_3d operator-(const float& num, const Vector_3d& vec)
	{
		return { num - vec.x, num - vec.y, num - vec.z };
	}
	Vector_3d operator*(const float& num, const Vector_3d& vec)
	{
		return { num * vec.x, num * vec.y, num * vec.z };
	}
	Vector_3d operator/(const float& num, const Vector_3d& vec)
	{
		return { num / vec.x, num / vec.y, num / vec.z };
	}
	Vector_3d operator+(const Vector_3d& vec, const float& num)
	{
		return { vec.x + num, vec.y + num, vec.z + num };
	}
	Vector_3d operator-(const Vector_3d& vec, const float& num)
	{
		return { vec.x - num, vec.y - num, vec.z - num };
	}
	Vector_3d operator*(const Vector_3d& vec, const float& num)
	{
		return { vec.x * num, vec.y * num, vec.z * num };
	}
	Vector_3d operator/(const Vector_3d& vec, const float& num)
	{
		return { vec.x / num, vec.y / num, vec.z / num };
	}

	float distance(Vector_3d vec_a, Vector_3d vec_b)
	{
		double vec_a_x = static_cast<double>(vec_a.x);
		double vec_a_y = static_cast<double>(vec_a.y);
		double vec_a_z = static_cast<double>(vec_a.z);
		double vec_b_x = static_cast<double>(vec_b.x);
		double vec_b_y = static_cast<double>(vec_b.y);
		double vec_b_z = static_cast<double>(vec_b.z);
		return sqrt((vec_b_x - vec_a_x) * (vec_b_x - vec_a_x) +
					(vec_b_y - vec_a_y) * (vec_b_y - vec_a_y) +
					(vec_b_z - vec_a_z) * (vec_b_z - vec_a_z));
	}
	float distance(Vector_3d vec_a, Vector_4d vec_b)
	{
		return distance(vec_a, static_cast<Vector_3d>(vec_b));
	}
	float distance(Vector_4d vec_a, Vector_3d vec_b)
	{
		return distance(static_cast<Vector_3d>(vec_a), vec_b);
	}
	float distance(Vector_4d vec_a, Vector_4d vec_b)
	{
		double vec_a_x = static_cast<double>(vec_a.x);
		double vec_a_y = static_cast<double>(vec_a.y);
		double vec_a_z = static_cast<double>(vec_a.z);
		double vec_a_w = static_cast<double>(vec_a.w);
		double vec_b_x = static_cast<double>(vec_b.x);
		double vec_b_y = static_cast<double>(vec_b.y);
		double vec_b_z = static_cast<double>(vec_b.z);
		double vec_b_w = static_cast<double>(vec_b.w);
		return sqrt((vec_b_x - vec_a_x) * (vec_b_x - vec_a_x) +
					(vec_b_y - vec_a_y) * (vec_b_y - vec_a_y) +
					(vec_b_z - vec_a_z) * (vec_b_z - vec_a_z) +
					(vec_b_w - vec_a_w) * (vec_b_w - vec_a_w));
	}

	float angle(Vector_3d vec_a, Vector_3d vec_b)
	{
		double arg = static_cast<double>((vec_a & vec_b) / (vec_a.length() * vec_b.length()));
		return static_cast<float>(acos(arg));
	}


	float Vector_4d::length()
	{
		double _x = static_cast<double>(x);
		double _y = static_cast<double>(y);
		double _z = static_cast<double>(z);
		return static_cast<float>(sqrt(_x * _x + _y * _y + _z * _z));
	}

	Vector_4d& Vector_4d::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}

	Vector_4d& Vector_4d::trunc()
	{
		x = x > 1.0f ? 1.0f : x;
		y = y > 1.0f ? 1.0f : y;
		z = z > 1.0f ? 1.0f : z;
		return *this;
	}

	Vector_4d& Vector_4d::operator=(const Vector_4d& vec)
	{
		if (this != &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
		}

		return *this;
	}

	Vector_4d& Vector_4d::operator+=(const float& num)
	{
		x += num; y += num; z += num;
		return *this;
	}
	Vector_4d& Vector_4d::operator-=(const float& num)
	{
		x -= num; y -= num; z -= num;
		return *this;
	}
	Vector_4d& Vector_4d::operator*=(const float& num)
	{
		x *= num; y *= num; z *= num;
		return *this;
	}
	Vector_4d& Vector_4d::operator/=(const float& num)
	{
		x /= num; y /= num; z /= num;
		return *this;
	}
	Vector_4d& Vector_4d::operator+=(const Vector_4d& vec)
	{
		x += vec.x; y += vec.y; z += vec.z;
		return *this;
	}
	Vector_4d& Vector_4d::operator-=(const Vector_4d& vec)
	{
		x -= vec.x; y -= vec.y; z -= vec.z;
		return *this;
	}
	Vector_4d& Vector_4d::operator*=(const Vector_4d& vec)
	{
		x *= vec.x; y *= vec.y; z *= vec.z;
		return *this;
	}
	Vector_4d& Vector_4d::operator/=(const Vector_4d& vec)
	{
		x /= vec.x; y /= vec.y; z /= vec.z;
		return *this;
	}

	Vector_4d::operator Vector_3d()
	{
		return { x, y, z };
	}

	Vector_4d operator+(const Vector_4d& vec_a, const Vector_4d& vec_b)
	{
		return { vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z, 1.0f };
	}
	Vector_4d operator-(const Vector_4d& vec_a, const Vector_4d& vec_b)
	{
		return { vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z, 1.0f };
	}
	Vector_4d operator*(const Vector_4d& vec_a, const Vector_4d& vec_b)
	{
		return { vec_a.x * vec_b.x, vec_a.y * vec_b.y, vec_a.z * vec_b.z, 1.0f };
	}
	Vector_4d operator/(const Vector_4d& vec_a, const Vector_4d& vec_b)
	{
		return { vec_a.x / vec_b.x, vec_a.y / vec_b.y, vec_a.z / vec_b.z, 1.0f };
	}

	bool operator==(const Vector_4d& vec_a, const Vector_4d& vec_b)
	{
		if ((vec_a.x - vec_b.x) * (vec_a.x - vec_b.x) > eps)
			return false;

		if ((vec_a.y - vec_b.y) * (vec_a.y - vec_b.y) > eps)
			return false;

		if ((vec_a.z - vec_b.z) * (vec_a.z - vec_b.z) > eps)
			return false;

		return true;
	}
	bool operator!=(const Vector_4d& vec_a, const Vector_4d& vec_b)
	{
		return !(vec_a == vec_b);
	}

	Vector_4d operator+(const float& num, const Vector_4d& vec)
	{
		return { num + vec.x, num + vec.y, num + vec.z, 1.0f };
	}
	Vector_4d operator-(const float& num, const Vector_4d& vec)
	{
		return { num - vec.x, num - vec.y, num - vec.z, 1.0f };
	}
	Vector_4d operator*(const float& num, const Vector_4d& vec)
	{
		return { num * vec.x, num * vec.y, num * vec.z, 1.0f };
	}
	Vector_4d operator/(const float& num, const Vector_4d& vec)
	{
		return { num / vec.x, num / vec.y, num / vec.z, 1.0f };
	}
	Vector_4d operator+(const Vector_4d& vec, const float& num)
	{
		return { vec.x + num, vec.y + num, vec.z + num, 1.0f };
	}
	Vector_4d operator-(const Vector_4d& vec, const float& num)
	{
		return { vec.x - num, vec.y - num, vec.z - num, 1.0f };
	}
	Vector_4d operator*(const Vector_4d& vec, const float& num)
	{
		return { vec.x * num, vec.y * num, vec.z * num, 1.0f };
	}
	Vector_4d operator/(const Vector_4d& vec, const float& num)
	{
		return { vec.x / num, vec.y / num, vec.z / num, 1.0f };
	}
}
