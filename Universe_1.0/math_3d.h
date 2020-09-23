/******************************************************************************
	 * File: math_3d.h
	 * Description: Contains utility classes and functions for 3D.
	 * Created: 09 Aug 2020
	 * Copyright: (C) 2020 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com

******************************************************************************/

#include <math.h>

namespace math_3d
{
	const float eps = 0.00000001f;
	const float pi = 3.14159265358979323846f;

	using vector_3d = struct vector_3d;
	using vector_4d = struct vector_4d;

	float factorial(int n);
	inline float radian_to_degree(float radian);
	inline float degree_to_radian(float degree);

	/**
	* @class vector_3d
	* 3D vector, can represent point or vector in 3D.
	*/
	struct vector_3d
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		vector_3d() {};
		vector_3d(float x, float y, float z) : x(x), y(y), z(z) {};
		vector_3d(const vector_3d& vec) = default;

		bool is_zero();
		float length();
		vector_3d& normalize();
		vector_3d& trunc();

		vector_3d& operator=(const vector_3d& vec);

		vector_3d& operator+=(const float& num);
		vector_3d& operator-=(const float& num);
		vector_3d& operator*=(const float& num);
		vector_3d& operator/=(const float& num);
		vector_3d& operator+=(const vector_3d& vec);
		vector_3d& operator-=(const vector_3d& vec);
		vector_3d& operator*=(const vector_3d& vec);
		vector_3d& operator/=(const vector_3d& vec);
		/**
		 * Scalar cross product
		 * a = (x1, y1, z1); b = (x2, y2, z2)
		 * a & b = 
		 * x1 * x2 + y1 * y2 + z1 * z2
		 */
		float operator&=(const vector_3d& vec);
		/**
		 * Vector cross product
		 * a = (x1, y1, z1); b = (x2, y2, z2)
		 * a ^ b = 
		 * (y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2)
		 */
		vector_3d& operator^=(const vector_3d& vec);

		operator vector_4d();
	};

	vector_3d operator+(const vector_3d& vec_a, const vector_3d& vec_b);
	vector_3d operator-(const vector_3d& vec_a, const vector_3d& vec_b);
	vector_3d operator*(const vector_3d& vec_a, const vector_3d& vec_b);
	vector_3d operator/(const vector_3d& vec_a, const vector_3d& vec_b);

	float operator&(const vector_3d& vec_a, const vector_3d& vec_b);
	vector_3d operator^(const vector_3d& vec_a, const vector_3d& vec_b);

	bool operator==(const vector_3d& vec_a, const vector_3d& vec_b);
	bool operator!=(const vector_3d& vec_a, const vector_3d& vec_b);

	vector_3d operator+(const float& num, const vector_3d& vec);
	vector_3d operator-(const float& num, const vector_3d& vec);
	vector_3d operator*(const float& num, const vector_3d& vec);
	vector_3d operator/(const float& num, const vector_3d& vec);
	vector_3d operator+(const vector_3d& vec, const float& num);
	vector_3d operator-(const vector_3d& vec, const float& num);
	vector_3d operator*(const vector_3d& vec, const float& num);
	vector_3d operator/(const vector_3d& vec, const float& num);

	float distance(vector_3d vec_a, vector_3d vec_b);
	float distance(vector_3d vec_a, vector_4d vec_b);
	float distance(vector_4d vec_a, vector_3d vec_b);
	float distance(vector_4d vec_a, vector_4d vec_b);

	float angle(vector_3d vec_a, vector_3d vec_b);


	/**
	* @class vector_4d
	* 4D vector, can represent point or vector in 4D.
	* Mostly used for colors.
	*/
	struct vector_4d
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		vector_4d() {};
		vector_4d(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
		vector_4d(const vector_4d& vec) = default;

		float length();
		vector_4d& normalize();
		vector_4d& trunc();

		vector_4d& operator= (const vector_4d& vec);

		vector_4d& operator+=(const float& num);
		vector_4d& operator-=(const float& num);
		vector_4d& operator*=(const float& num);
		vector_4d& operator/=(const float& num);
		vector_4d& operator+=(const vector_4d& vec);
		vector_4d& operator-=(const vector_4d& vec);
		vector_4d& operator*=(const vector_4d& vec);
		vector_4d& operator/=(const vector_4d& vec);

		operator vector_3d();
	};

	vector_4d operator+(const vector_4d& vec_a, const vector_4d& vec_b);
	vector_4d operator-(const vector_4d& vec_a, const vector_4d& vec_b);
	vector_4d operator*(const vector_4d& vec_a, const vector_4d& vec_b);
	vector_4d operator/(const vector_4d& vec_a, const vector_4d& vec_b);

	bool operator==(const vector_4d& vec_a, const vector_4d& vec_b);
	bool operator!=(const vector_4d& vec_a, const vector_4d& vec_b);

	vector_4d operator+(const float& num, const vector_4d& vec);
	vector_4d operator-(const float& num, const vector_4d& vec);
	vector_4d operator*(const float& num, const vector_4d& vec);
	vector_4d operator/(const float& num, const vector_4d& vec);
	vector_4d operator+(const vector_4d& vec, const float& num);
	vector_4d operator-(const vector_4d& vec, const float& num);
	vector_4d operator*(const vector_4d& vec, const float& num);
	vector_4d operator/(const vector_4d& vec, const float& num);
}

