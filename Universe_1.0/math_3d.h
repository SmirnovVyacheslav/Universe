/******************************************************************************
	 * File: math_3d.h
	 * Description: Contains utility classes and functions for 3D.
	 * Created: 09 Aug 2020
	 * Copyright: (C) 2020 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com

******************************************************************************/

#include <math.h>

namespace Math_3d
{
	const float eps = 0.00000001f;
	const float pi = 3.14159265358979323846f;

	using Vector_3d = struct Vector_3d;
	using Vector_4d = struct Vector_4d;

	float factorial(int n);
	inline float radian_to_degree(float radian);
	inline float degree_to_radian(float degree);

	/**
	* @class Vector_3d
	* 3D vector, can represent point or vector in 3D.
	*/
	struct Vector_3d
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Vector_3d() {};
		Vector_3d(float x, float y, float z) : x(x), y(y), z(z) {};
		Vector_3d(const Vector_3d& vec) = default;

		bool is_zero();
		float length();
		Vector_3d& normalize();
		Vector_3d& trunc();

		Vector_3d& operator=(const Vector_3d& vec);

		Vector_3d& operator+=(const float& num);
		Vector_3d& operator-=(const float& num);
		Vector_3d& operator*=(const float& num);
		Vector_3d& operator/=(const float& num);
		Vector_3d& operator+=(const Vector_3d& vec);
		Vector_3d& operator-=(const Vector_3d& vec);
		Vector_3d& operator*=(const Vector_3d& vec);
		Vector_3d& operator/=(const Vector_3d& vec);
		/**
		 * Scalar cross product
		 * a = (x1, y1, z1); b = (x2, y2, z2)
		 * a & b = 
		 * x1 * x2 + y1 * y2 + z1 * z2
		 */
		float operator&=(const Vector_3d& vec);
		/**
		 * Vector cross product
		 * a = (x1, y1, z1); b = (x2, y2, z2)
		 * a ^ b = 
		 * (y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2)
		 */
		Vector_3d& operator^=(const Vector_3d& vec);

		operator Vector_4d();
	};

	Vector_3d operator+(const Vector_3d& vec_a, const Vector_3d& vec_b);
	Vector_3d operator-(const Vector_3d& vec_a, const Vector_3d& vec_b);
	Vector_3d operator*(const Vector_3d& vec_a, const Vector_3d& vec_b);
	Vector_3d operator/(const Vector_3d& vec_a, const Vector_3d& vec_b);

	float operator&(const Vector_3d& vec_a, const Vector_3d& vec_b);
	Vector_3d operator^(const Vector_3d& vec_a, const Vector_3d& vec_b);

	bool operator==(const Vector_3d& vec_a, const Vector_3d& vec_b);
	bool operator!=(const Vector_3d& vec_a, const Vector_3d& vec_b);

	Vector_3d operator+(const float& num, const Vector_3d& vec);
	Vector_3d operator-(const float& num, const Vector_3d& vec);
	Vector_3d operator*(const float& num, const Vector_3d& vec);
	Vector_3d operator/(const float& num, const Vector_3d& vec);
	Vector_3d operator+(const Vector_3d& vec, const float& num);
	Vector_3d operator-(const Vector_3d& vec, const float& num);
	Vector_3d operator*(const Vector_3d& vec, const float& num);
	Vector_3d operator/(const Vector_3d& vec, const float& num);

	float distance(Vector_3d vec_a, Vector_3d vec_b);
	float distance(Vector_3d vec_a, Vector_4d vec_b);
	float distance(Vector_4d vec_a, Vector_3d vec_b);
	float distance(Vector_4d vec_a, Vector_4d vec_b);

	float angle(Vector_3d vec_a, Vector_3d vec_b);


	/**
	* @class Vector_4d
	* 4D vector, can represent point or vector in 4D.
	* Mostly used for colors.
	*/
	struct Vector_4d
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		Vector_4d() {};
		Vector_4d(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
		Vector_4d(const Vector_4d& vec) = default;

		float length();
		Vector_4d& normalize();
		Vector_4d& trunc();

		Vector_4d& operator= (const Vector_4d& vec);

		Vector_4d& operator+=(const float& num);
		Vector_4d& operator-=(const float& num);
		Vector_4d& operator*=(const float& num);
		Vector_4d& operator/=(const float& num);
		Vector_4d& operator+=(const Vector_4d& vec);
		Vector_4d& operator-=(const Vector_4d& vec);
		Vector_4d& operator*=(const Vector_4d& vec);
		Vector_4d& operator/=(const Vector_4d& vec);

		operator Vector_3d();
	};

	Vector_4d operator+(const Vector_4d& vec_a, const Vector_4d& vec_b);
	Vector_4d operator-(const Vector_4d& vec_a, const Vector_4d& vec_b);
	Vector_4d operator*(const Vector_4d& vec_a, const Vector_4d& vec_b);
	Vector_4d operator/(const Vector_4d& vec_a, const Vector_4d& vec_b);

	bool operator==(const Vector_4d& vec_a, const Vector_4d& vec_b);
	bool operator!=(const Vector_4d& vec_a, const Vector_4d& vec_b);

	Vector_4d operator+(const float& num, const Vector_4d& vec);
	Vector_4d operator-(const float& num, const Vector_4d& vec);
	Vector_4d operator*(const float& num, const Vector_4d& vec);
	Vector_4d operator/(const float& num, const Vector_4d& vec);
	Vector_4d operator+(const Vector_4d& vec, const float& num);
	Vector_4d operator-(const Vector_4d& vec, const float& num);
	Vector_4d operator*(const Vector_4d& vec, const float& num);
	Vector_4d operator/(const Vector_4d& vec, const float& num);
}

