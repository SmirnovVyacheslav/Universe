#include"x_vector.h"

Vector3& Vector3::operator=(const Vector3& vec)
{
	if (this != &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	return *this;
}

Vector3 Vector3::normalize()
{
	return Vector3(*this) * (1 / length());
}

float Vector3::length()
{
	return static_cast<float>(sqrt(static_cast<double>(x * x + y * y + z * z)));
}

Vector3 Vector3::trunc()
{
	x = x > 1.0f ? 1.0f : x;
	y = y > 1.0f ? 1.0f : y;
	z = z > 1.0f ? 1.0f : z;
	return Vector3(*this);
}

Vector3 operator+(Vector3& vec, const float& num)
{
	return Vector3(vec.x + num, vec.y + num, vec.z + num);
}
Vector3 operator+(const float& num, Vector3& vec)
{
	return Vector3(num + vec.x, num + vec.y, num + vec.z);
}
Vector3 operator-(Vector3& vec, const float& num)
{
	return Vector3(vec.x - num, vec.y - num, vec.z - num);
}
Vector3 operator-(const float& num, Vector3& vec)
{
	return Vector3(num - vec.x, num - vec.y, num - vec.z);
}
Vector3 operator*(Vector3& vec, const float& num)
{
	return Vector3(vec.x * num, vec.y * num, vec.z * num);
}
Vector3 operator*(const float& num, Vector3& vec)
{
	return Vector3(num * vec.x, num * vec.y, num * vec.z);
}
Vector3 operator/(Vector3& vec, const float& num)
{
	return Vector3(vec.x / num, vec.y / num, vec.z / num);
}
Vector3 operator/(const float& num, Vector3& vec)
{
	return Vector3(num / vec.x, num / vec.y, num / vec.z);
}

bool operator>(Vector3& vec, const float& num)
{
	if (vec.x < num)
		return false;
	if (vec.y < num)
		return false;
	if (vec.z < num)
		return false;
	return true;
}
bool operator>(const float& num, Vector3& vec)
{
	if (num < vec.x)
		return false;
	if (num < vec.y)
		return false;
	if (num < vec.z)
		return false;
	return true;
}
bool operator<(Vector3& vec, const float& num)
{
	if (vec.x > num)
		return false;
	if (vec.y > num)
		return false;
	if (vec.z > num)
		return false;
	return true;
}
bool operator<(const float& num, Vector3& vec)
{
	if (num > vec.x)
		return false;
	if (num > vec.y)
		return false;
	if (num > vec.z)
		return false;
	return true;
}

Vector3 Vector3::operator+(const Vector3& vec)
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}
Vector3 Vector3::operator-(const Vector3& vec)
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}
Vector3 Vector3::operator*(const Vector3& vec)
{
	return Vector3(x * vec.x, y * vec.y, z * vec.z);
}
Vector3 Vector3::operator/(const Vector3& vec)
{
	return Vector3(x / vec.x, y / vec.y, z / vec.z);
}
//Scalar *
float Vector3::operator&(const Vector3& vec)
{
	return x * vec.x + y * vec.y + z * vec.z;
}
//Vector *
Vector3 Vector3::operator^(const Vector3& vec)
{
	return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

bool Vector3::operator==(const Vector3& vec)
{
	if ((x - vec.x) * (x - vec.x) > 0.000001f)
	{
		return false;
	}

	if ((y - vec.y) * (y - vec.y) > 0.000001f)
	{
		return false;
	}

	if ((z - vec.z) * (z - vec.z) > 0.000001f)
	{
		return false;
	}

	return true;
}

bool Vector3::operator!=(const Vector3& vec)
{
	if ((x - vec.x) * (x - vec.x) > 0.000001f)
	{
		return true;
	}

	if ((y - vec.y) * (y - vec.y) > 0.000001f)
	{
		return true;
	}

	if ((z - vec.z) * (z - vec.z) > 0.000001f)
	{
		return true;
	}

	return false;
}

Vector3::operator Vector4()
{
	return { x, y, z, 0.0f };
}



float dist(Vector3 vecA, Vector3 vecB)
{
	return sqrt((vecB.x - vecA.x) * (vecB.x - vecA.x) + (vecB.y - vecA.y) * (vecB.y - vecA.y) + (vecB.z - vecA.z) * (vecB.z - vecA.z));
}
float dist(Vector3 vecA, Vector4 vecB)
{
	return sqrt((vecB.x - vecA.x) * (vecB.x - vecA.x) + (vecB.y - vecA.y) * (vecB.y - vecA.y) + (vecB.z - vecA.z) * (vecB.z - vecA.z));
}
float dist(Vector4 vecA, Vector3 vecB)
{
	return sqrt((vecB.x - vecA.x) * (vecB.x - vecA.x) + (vecB.y - vecA.y) * (vecB.y - vecA.y) + (vecB.z - vecA.z) * (vecB.z - vecA.z));
}
float dist(Vector4 vecA, Vector4 vecB)
{
	return sqrt((vecB.x - vecA.x) * (vecB.x - vecA.x) + (vecB.y - vecA.y) * (vecB.y - vecA.y) + (vecB.z - vecA.z) * (vecB.z - vecA.z) + (vecB.w - vecA.w) * (vecB.w - vecA.w));
}



Vector4& Vector4::operator=(const Vector4& vec)
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

Vector4& Vector4::normalize()
{
	return Vector4(*this) * (1 / length());
}

float Vector4::length()
{
	return static_cast<float>(sqrt(static_cast<double>(x * x + y * y + z * z + w * w)));
}

Vector4 Vector4::trunc()
{
	x = x > 1.0f ? 1.0f : x;
	y = y > 1.0f ? 1.0f : y;
	z = z > 1.0f ? 1.0f : z;
	return Vector4(*this);
}

Vector4 Vector4::operator+(const Vector4& vec)
{
	return Vector4(x + vec.x, y + vec.y, z + vec.z, 1.0f);
}
Vector4 Vector4::operator-(const Vector4& vec)
{
	return Vector4(x - vec.x, y - vec.y, z - vec.z, 1.0f);
}
Vector4 Vector4::operator*(const Vector4& vec)
{
	return Vector4(x * vec.x, y * vec.y, z * vec.z, 1.0f);
}
Vector4 Vector4::operator/(const Vector4& vec)
{
	return Vector4(x / vec.x, y / vec.y, z / vec.z, 1.0f);
}

Vector4 operator+(Vector4& vec, const float& num)
{
	return Vector4(vec.x + num, vec.y + num, vec.z + num, 1.0f);
}
Vector4 operator+(const float& num, Vector4& vec)
{
	return Vector4(num + vec.x, num + vec.y, num + vec.z, 1.0f);
}
Vector4 operator-(Vector4& vec, const float& num)
{
	return Vector4(vec.x - num, vec.y - num, vec.z - num, 1.0f);
}
Vector4 operator-(const float& num, Vector4& vec)
{
	return Vector4(num - vec.x, num - vec.y, num - vec.z, 1.0f);
}
Vector4 operator*(Vector4& vec, const float& num)
{
	return Vector4(vec.x * num, vec.y * num, vec.z * num, 1.0f);
}
Vector4 operator*(const float& num, Vector4& vec)
{
	return Vector4(num * vec.x, num * vec.y, num * vec.z, 1.0f);
}
Vector4 operator/(Vector4& vec, const float& num)
{
	return Vector4(vec.x / num, vec.y / num, vec.z / num, 1.0f);
}
Vector4 operator/(const float& num, Vector4& vec)
{
	return Vector4(num / vec.x, num / vec.y, num / vec.z, 1.0f);
}