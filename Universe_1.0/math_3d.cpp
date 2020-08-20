/******************************************************************************
	 * File: math_3d.cpp
	 * Description: Contains utility classes and functions for 3D.
	 * Created: 09 Aug 2020
	 * Copyright: (C) 2020 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com

******************************************************************************/

#include "math_3d.h"

namespace math_3d
{
	bool vector_3d::is_zero()
	{
		return (x + y + z) < eps;
	}

	float vector_3d::length()
	{
		double _x = static_cast<double>(x);
		double _y = static_cast<double>(y);
		double _z = static_cast<double>(z);
		return static_cast<float>(sqrt(_x * _x + _y * _y + _z * _z));
	}

	vector_3d& vector_3d::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}

	vector_3d& vector_3d::trunc()
	{
		x = x > 1.0f ? 1.0f : x;
		y = y > 1.0f ? 1.0f : y;
		z = z > 1.0f ? 1.0f : z;
		return *this;
	}

	vector_3d& vector_3d::operator=(const vector_3d& vec)
	{
		if (this != &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		return *this;
	}

	vector_3d& vector_3d::operator+=(const float& num)
	{
		x += num; y += num; z += num;
		return *this;
	}
	vector_3d& vector_3d::operator-=(const float& num)
	{
		x -= num; y -= num; z -= num;
		return *this;
	}
	vector_3d& vector_3d::operator*=(const float& num)
	{
		x *= num; y *= num; z *= num;
		return *this;
	}
	vector_3d& vector_3d::operator/=(const float& num)
	{
		x /= num; y /= num; z /= num;
		return *this;
	}
	vector_3d& vector_3d::operator+=(const vector_3d& vec)
	{
		x += vec.x; y += vec.y; z += vec.z;
		return *this;
	}
	vector_3d& vector_3d::operator-=(const vector_3d& vec)
	{
		x -= vec.x; y -= vec.y; z -= vec.z;
		return *this;
	}
	vector_3d& vector_3d::operator*=(const vector_3d& vec)
	{
		x *= vec.x; y *= vec.y; z *= vec.z;
		return *this;
	}
	vector_3d& vector_3d::operator/=(const vector_3d& vec)
	{
		x /= vec.x; y /= vec.y; z /= vec.z;
		return *this;
	}

	/**
	 * Scalar cross product
	 */
	float vector_3d::operator&=(const vector_3d& vec)
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	/**
	 * Vector cross product
	 */
	vector_3d& vector_3d::operator^=(const vector_3d& vec)
	{
		x = y * vec.z - z * vec.y;
		y = z * vec.x - x * vec.z;
		z = x * vec.y - y * vec.x;
		return *this;
	}

	vector_3d::operator vector_4d()
	{
		return { x, y, z, 0.0f };
	}

	vector_3d operator+(const vector_3d& vec_a, const vector_3d& vec_b)
	{
		return { vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z };
	}
	vector_3d operator-(const vector_3d& vec_a, const vector_3d& vec_b)
	{
		return { vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z };
	}
	vector_3d operator*(const vector_3d& vec_a, const vector_3d& vec_b)
	{
		return { vec_a.x * vec_b.x, vec_a.y * vec_b.y, vec_a.z * vec_b.z };
	}
	vector_3d operator/(const vector_3d& vec_a, const vector_3d& vec_b)
	{
		return { vec_a.x / vec_b.x, vec_a.y / vec_b.y, vec_a.z / vec_b.z };
	}
	/**
	 * Scalar cross product
	 */
	float operator&(const vector_3d& vec_a, const vector_3d& vec_b)
	{
		return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
	}
	/**
	 * Vector cross product
	 */
	vector_3d operator^(const vector_3d& vec_a, const vector_3d& vec_b)
	{
		return { vec_a.y * vec_b.z - vec_a.z * vec_b.y,
				 vec_a.z * vec_b.x - vec_a.x * vec_b.z,
				 vec_a.x * vec_b.y - vec_a.y * vec_b.x };
	}

	bool operator==(const vector_3d& vec_a, const vector_3d& vec_b)
	{
		if ((vec_a.x - vec_b.x) * (vec_a.x - vec_b.x) > eps)
			return false;

		if ((vec_a.y - vec_b.y) * (vec_a.y - vec_b.y) > eps)
			return false;

		if ((vec_a.z - vec_b.z) * (vec_a.z - vec_b.z) > eps)
			return false;

		return true;
	}
	bool operator!=(const vector_3d& vec_a, const vector_3d& vec_b)
	{
		return !(vec_a == vec_b);
	}

	vector_3d operator+(const float& num, const vector_3d& vec)
	{
		return { num + vec.x, num + vec.y, num + vec.z };
	}
	vector_3d operator-(const float& num, const vector_3d& vec)
	{
		return { num - vec.x, num - vec.y, num - vec.z };
	}
	vector_3d operator*(const float& num, const vector_3d& vec)
	{
		return { num * vec.x, num * vec.y, num * vec.z };
	}
	vector_3d operator/(const float& num, const vector_3d& vec)
	{
		return { num / vec.x, num / vec.y, num / vec.z };
	}
	vector_3d operator+(const vector_3d& vec, const float& num)
	{
		return { vec.x + num, vec.y + num, vec.z + num };
	}
	vector_3d operator-(const vector_3d& vec, const float& num)
	{
		return { vec.x - num, vec.y - num, vec.z - num };
	}
	vector_3d operator*(const vector_3d& vec, const float& num)
	{
		return { vec.x * num, vec.y * num, vec.z * num };
	}
	vector_3d operator/(const vector_3d& vec, const float& num)
	{
		return { vec.x / num, vec.y / num, vec.z / num };
	}

	float distance(vector_3d vec_a, vector_3d vec_b)
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
	float distance(vector_3d vec_a, vector_4d vec_b)
	{
		return distance(vec_a, static_cast<vector_3d>(vec_b));
	}
	float distance(vector_4d vec_a, vector_3d vec_b)
	{
		return distance(static_cast<vector_3d>(vec_a), vec_b);
	}
	float distance(vector_4d vec_a, vector_4d vec_b)
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

	float angle(vector_3d vec_a, vector_3d vec_b)
	{
		double arg = static_cast<double>((vec_a & vec_b) / (vec_a.length() * vec_b.length()));
		return static_cast<float>(acos(arg));
	}


	float vector_4d::length()
	{
		double _x = static_cast<double>(x);
		double _y = static_cast<double>(y);
		double _z = static_cast<double>(z);
		return static_cast<float>(sqrt(_x * _x + _y * _y + _z * _z));
	}

	vector_4d& vector_4d::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}

	vector_4d& vector_4d::trunc()
	{
		x = x > 1.0f ? 1.0f : x;
		y = y > 1.0f ? 1.0f : y;
		z = z > 1.0f ? 1.0f : z;
		return *this;
	}

	vector_4d& vector_4d::operator=(const vector_4d& vec)
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

	vector_4d& vector_4d::operator+=(const float& num)
	{
		x += num; y += num; z += num;
		return *this;
	}
	vector_4d& vector_4d::operator-=(const float& num)
	{
		x -= num; y -= num; z -= num;
		return *this;
	}
	vector_4d& vector_4d::operator*=(const float& num)
	{
		x *= num; y *= num; z *= num;
		return *this;
	}
	vector_4d& vector_4d::operator/=(const float& num)
	{
		x /= num; y /= num; z /= num;
		return *this;
	}
	vector_4d& vector_4d::operator+=(const vector_4d& vec)
	{
		x += vec.x; y += vec.y; z += vec.z;
		return *this;
	}
	vector_4d& vector_4d::operator-=(const vector_4d& vec)
	{
		x -= vec.x; y -= vec.y; z -= vec.z;
		return *this;
	}
	vector_4d& vector_4d::operator*=(const vector_4d& vec)
	{
		x *= vec.x; y *= vec.y; z *= vec.z;
		return *this;
	}
	vector_4d& vector_4d::operator/=(const vector_4d& vec)
	{
		x /= vec.x; y /= vec.y; z /= vec.z;
		return *this;
	}

	vector_4d::operator vector_3d()
	{
		return { x, y, z };
	}

	vector_4d operator+(const vector_4d& vec_a, const vector_4d& vec_b)
	{
		return { vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z, 1.0f };
	}
	vector_4d operator-(const vector_4d& vec_a, const vector_4d& vec_b)
	{
		return { vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z, 1.0f };
	}
	vector_4d operator*(const vector_4d& vec_a, const vector_4d& vec_b)
	{
		return { vec_a.x * vec_b.x, vec_a.y * vec_b.y, vec_a.z * vec_b.z, 1.0f };
	}
	vector_4d operator/(const vector_4d& vec_a, const vector_4d& vec_b)
	{
		return { vec_a.x / vec_b.x, vec_a.y / vec_b.y, vec_a.z / vec_b.z, 1.0f };
	}

	bool operator==(const vector_4d& vec_a, const vector_4d& vec_b)
	{
		if ((vec_a.x - vec_b.x) * (vec_a.x - vec_b.x) > eps)
			return false;

		if ((vec_a.y - vec_b.y) * (vec_a.y - vec_b.y) > eps)
			return false;

		if ((vec_a.z - vec_b.z) * (vec_a.z - vec_b.z) > eps)
			return false;

		return true;
	}
	bool operator!=(const vector_4d& vec_a, const vector_4d& vec_b)
	{
		return !(vec_a == vec_b);
	}

	vector_4d operator+(const float& num, const vector_4d& vec)
	{
		return { num + vec.x, num + vec.y, num + vec.z, 1.0f };
	}
	vector_4d operator-(const float& num, const vector_4d& vec)
	{
		return { num - vec.x, num - vec.y, num - vec.z, 1.0f };
	}
	vector_4d operator*(const float& num, const vector_4d& vec)
	{
		return { num * vec.x, num * vec.y, num * vec.z, 1.0f };
	}
	vector_4d operator/(const float& num, const vector_4d& vec)
	{
		return { num / vec.x, num / vec.y, num / vec.z, 1.0f };
	}
	vector_4d operator+(const vector_4d& vec, const float& num)
	{
		return { vec.x + num, vec.y + num, vec.z + num, 1.0f };
	}
	vector_4d operator-(const vector_4d& vec, const float& num)
	{
		return { vec.x - num, vec.y - num, vec.z - num, 1.0f };
	}
	vector_4d operator*(const vector_4d& vec, const float& num)
	{
		return { vec.x * num, vec.y * num, vec.z * num, 1.0f };
	}
	vector_4d operator/(const vector_4d& vec, const float& num)
	{
		return { vec.x / num, vec.y / num, vec.z / num, 1.0f };
	}
}
