#include <math.h>

using Vector3 = struct Vector3;
using Vector4 = struct Vector4;

struct Vector3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vector3() {};
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3(const Vector3& vec) = default;

	Vector3& normalize();

	float length();

	Vector3& operator= (const Vector3& vec);
	Vector3 operator+(const Vector3& vec);
	Vector3 operator-(const Vector3& vec);
	Vector3 operator*(const Vector3& vec);
	Vector3 operator/(const Vector3& vec);
	float operator&(const Vector3& vec);
	Vector3 operator^(const Vector3& vec);

	bool operator==(const Vector3& vec);
	bool operator!=(const Vector3& vec);

	Vector3& trunc();

	operator Vector4();

	bool is_zero();

	Vector3 rotate_on_x(float angle);
	Vector3 rotate_on_y(float angle);
	Vector3 rotate_on_z(float angle);
};

Vector3 operator+(Vector3& vec, const float& num);
Vector3 operator+(const float& num, Vector3& vec);
Vector3 operator-(Vector3& vec, const float& num);
Vector3 operator-(const float& num, Vector3& vec);
Vector3 operator*(Vector3& vec, const float& num);
Vector3 operator*(const float& num, Vector3& vec);
Vector3 operator/(Vector3& vec, const float& num);
Vector3 operator/(const float& num, Vector3& vec);

bool operator>(Vector3& vec, const float& num);
bool operator>(const float& num, Vector3& vec);
bool operator<(Vector3& vec, const float& num);
bool operator<(const float& num, Vector3& vec);

float dist(Vector3 vecA, Vector3 vecB);
float dist(Vector3 vecA, Vector4 vecB);
float dist(Vector4 vecA, Vector3 vecB);
float dist(Vector4 vecA, Vector4 vecB);

float angle(Vector3 vecA, Vector3 vecB);

struct Vector4
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	Vector4() {};
	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};

	Vector4& operator= (const Vector4& vec);

	Vector4& normalize();

	float length();

	Vector4 operator+(const Vector4& vec);
	Vector4 operator-(const Vector4& vec);
	Vector4 operator*(const Vector4& vec);
	Vector4 operator/(const Vector4& vec);

	Vector4 trunc();

	operator Vector3();
};

Vector4 operator+(Vector4& vec, const float& num);
Vector4 operator+(const float& num, Vector4& vec);
Vector4 operator-(Vector4& vec, const float& num);
Vector4 operator-(const float& num, Vector4& vec);
Vector4 operator*(Vector4& vec, const float& num);
Vector4 operator*(const float& num, Vector4& vec);
Vector4 operator/(Vector4& vec, const float& num);
Vector4 operator/(const float& num, Vector4& vec);