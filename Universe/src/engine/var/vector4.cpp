// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_vector4.h"


namespace engine
{
    vector4::vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {}

    vector4::vector4(fp32 x, fp32 y, fp32 z, fp32 w) : x(x), y(y), z(z), w(w)
    {}

    vector4::vector4(const vector<4> vec)
    {
        data = vec;
    }

    vector4::operator const fp32* () const
    {
        return reinterpret_cast<const fp32*>(this);
    }

    fp32& vector4::operator[](const int32 index)
    {
       return data[index];
    }

    const fp32& vector4::operator[](const int32 index) const
    {
       return data[index];
    }


    const fp32 length(const vector4& vec)
    {
        return length(vec.data);
    }

    const vector4 normalize(const vector4& vec)
    {
        return normalize(vec.data);
    }

    const vector4 operator+(const vector4& vec_a, const vector4& vec_b)
    {
        return vec_a.data + vec_b.data;
    }

    const vector4 operator-(const vector4& vec_a, const vector4& vec_b)
    {
        return vec_a.data - vec_b.data;
    }

    const vector4 operator+(const vector4& vec, const fp32& num) 
    {
        return vec.data + num;
    }

    const vector4 operator-(const vector4& vec, const fp32& num)
    {
        return vec.data - num;
    }

    const vector4 operator*(const vector4& vec, const fp32& num)
    {
        return vec.data * num;
    }

    const vector4 operator/(const vector4& vec, const fp32& num)
    {
        return vec.data / num;
    }

    const vector4 operator+(const fp32& num, const vector4& vec)
    {
        return num + vec.data;
    }

    const vector4 operator-(const fp32& num, const vector4& vec)
    {
        return num - vec.data;
    }

    const vector4 operator*(const fp32& num, const vector4& vec)
    {
        return num * vec.data;
    }

    const vector4 operator/(const fp32& num, const vector4& vec)
    {
        return num / vec.data;
    }

    bool operator==(const vector4& vec_a, const vector4& vec_b)
    {
        return vec_a.data == vec_b.data;
    }

    bool operator!=(const vector4& vec_a, const vector4& vec_b)
    {
        return vec_a.data != vec_b.data;
    }

    // Scalar product
    const fp32 operator*(const vector4& vec_a, const vector4& vec_b)
    {
        return vec_a.data * vec_b.data;
    }

    std::istream& operator>>(std::istream& in_stream, vector4& vec)
    {
        in_stream >> vec.data;
        return in_stream;
    }

    std::ostream& operator<<(std::ostream& out_stream, const vector4& vec)
    {
        out_stream << vec.data;
        return out_stream;
    }
}
