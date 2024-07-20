// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_vector3.h"


namespace engine
{
    vector3::vector3() : x(0.0f), y(0.0f), z(0.0f)
    {}

    vector3::vector3(fp32 x, fp32 y, fp32 z) : x(x), y(y), z(z)
    {}

    vector3::vector3(const vector<3> vec)
    {
        data = vec;
    }

    vector3::operator const fp32* () const
    {
        return reinterpret_cast<const fp32*>(this);
    }

    fp32& vector3::operator[](const int32 index)
    {
        return data[index];
    }

    const fp32& vector3::operator[](const int32 index) const
    {
        return data[index];
    }


    const fp32 length(const vector3& vec)
    {
        return length(vec.data);
    }

    const vector3 normalize(const vector3& vec)
    {
        return normalize(vec.data);
    }

    const vector3 operator+(const vector3& vec_a, const vector3& vec_b)
    {
        return vec_a.data + vec_b.data;
    }

    const vector3 operator-(const vector3& vec_a, const vector3& vec_b)
    {
        return vec_a.data - vec_b.data;
    }

    const vector3 operator+(const vector3& vec, const fp32& num)
    {
        return vec.data + num;
    }

    const vector3 operator-(const vector3& vec, const fp32& num)
    {
        return vec.data - num;
    }

    const vector3 operator*(const vector3& vec, const fp32& num)
    {
        return vec.data * num;
    }

    const vector3 operator/(const vector3& vec, const fp32& num)
    {
        return vec.data / num;
    }

    const vector3 operator+(const fp32& num, const vector3& vec)
    {
        return num + vec.data;
    }

    const vector3 operator-(const fp32& num, const vector3& vec)
    {
        return num - vec.data;
    }

    const vector3 operator*(const fp32& num, const vector3& vec)
    {
        return num * vec.data;
    }

    const vector3 operator/(const fp32& num, const vector3& vec)
    {
        return num / vec.data;
    }

    bool operator==(const vector3& vec_a, const vector3& vec_b)
    {
        return vec_a.data == vec_b.data;
    }

    bool operator!=(const vector3& vec_a, const vector3& vec_b)
    {
        return vec_a.data != vec_b.data;
    }

    // Scalar product
    const fp32 operator*(const vector3& vec_a, const vector3& vec_b)
    {
        return vec_a.data * vec_b.data;
    }

    // Vector product
    const vector3 operator^(const vector3& vec_a, const vector3& vec_b)
    {
        return { vec_a.y * vec_b.z - vec_a.z * vec_b.y,
                 vec_a.z * vec_b.x - vec_a.x * vec_b.z,
                 vec_a.x * vec_b.y - vec_a.y * vec_b.x };
    }

    std::istream& operator>>(std::istream& in_stream, vector3& vec)
    {
        in_stream >> vec.data;
        return in_stream;
    }

    std::ostream& operator<<(std::ostream& out_stream, const vector3& vec)
    {
        out_stream << vec.data;
        return out_stream;
    }
}
