// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "vector_3.h"


namespace engine {
    vector_3::vector_3() : x(0.0f), y(0.0f), z(0.0f) {
    }
    vector_3::vector_3(real32 x, real32 y, real32 z) : x(x), y(y), z(z) {
    }
    vector_3::vector_3(const vector<3> vec) {
        data = vec;
    }
    real32& vector_3::operator[](const int32 index) {
        return data[index];
    }
    const real32& vector_3::operator[](const int32 index) const {
        return data[index];
    }


    const real32 length(const vector_3& vec) {
        return length(vec.data);
    }
    const vector_3 normalize(const vector_3& vec) {
        return normalize(vec.data);
    }
    const vector_3 operator+(const vector_3& vec_a, const vector_3& vec_b) {
        return vec_a.data + vec_b.data;
    }
    const vector_3 operator-(const vector_3& vec_a, const vector_3& vec_b) {
        return vec_a.data - vec_b.data;
    }
    const vector_3 operator+(const vector_3& vec, const real32& num) {
        return vec.data + num;
    }
    const vector_3 operator-(const vector_3& vec, const real32& num) {
        return vec.data - num;
    }
    const vector_3 operator*(const vector_3& vec, const real32& num) {
        return vec.data * num;
    }
    const vector_3 operator/(const vector_3& vec, const real32& num) {
        return vec.data / num;
    }
    const vector_3 operator+(const real32& num, const vector_3& vec) {
        return num + vec.data;
    }
    const vector_3 operator-(const real32& num, const vector_3& vec) {
        return num - vec.data;
    }
    const vector_3 operator*(const real32& num, const vector_3& vec) {
        return num * vec.data;
    }
    const vector_3 operator/(const real32& num, const vector_3& vec) {
        return num / vec.data;
    }
    bool operator==(const vector_3& vec_a, const vector_3& vec_b) {
        return vec_a.data == vec_b.data;
    }
    bool operator!=(const vector_3& vec_a, const vector_3& vec_b) {
        return vec_a.data != vec_b.data;
    }
    // Scalar product
    const real32 operator*(const vector_3& vec_a, const vector_3& vec_b) {
        return vec_a.data * vec_b.data;
    }
    // Vector product
    const vector_3 operator^(const vector_3& vec_a, const vector_3& vec_b) {
        return { vec_a.y * vec_b.z - vec_a.z * vec_b.y,
                 vec_a.z * vec_b.x - vec_a.x * vec_b.z,
                 vec_a.x * vec_b.y - vec_a.y * vec_b.x };
    }
    std::istream& operator>>(std::istream& in_stream, vector_3& vec) {
        in_stream >> vec.data;
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const vector_3& vec) {
        out_stream << vec.data;
        return out_stream;
    }
}
