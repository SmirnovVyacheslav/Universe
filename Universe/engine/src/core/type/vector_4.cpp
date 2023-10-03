// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "vector_4.h"


namespace engine {
    vector_4::vector_4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
    }
    vector_4::vector_4(real32 x, real32 y, real32 z, real32 w) : x(x), y(y), z(z), w(w) {
    }
    vector_4::vector_4(const vector<4> vec) {
        data = vec;
    }
    real32& vector_4::operator[](const int32 index) {
       return data[index];
    }
    const real32& vector_4::operator[](const int32 index) const {
       return data[index];
    }


    const real32 length(const vector_4& vec) {
        return length(vec.data);
    }
    const vector_4 normalize(const vector_4& vec) {
        return normalize(vec.data);
    }
    const vector_4 operator+(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data + vec_b.data;
    }
    const vector_4 operator-(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data - vec_b.data;
    }
    const vector_4 operator+(const vector_4& vec, const real32& num) {
        return vec.data + num;
    }
    const vector_4 operator-(const vector_4& vec, const real32& num) {
        return vec.data - num;
    }
    const vector_4 operator*(const vector_4& vec, const real32& num) {
        return vec.data * num;
    }
    const vector_4 operator/(const vector_4& vec, const real32& num) {
        return vec.data / num;
    }
    const vector_4 operator+(const real32& num, const vector_4& vec) {
        return num + vec.data;
    }
    const vector_4 operator-(const real32& num, const vector_4& vec) {
        return num - vec.data;
    }
    const vector_4 operator*(const real32& num, const vector_4& vec) {
        return num * vec.data;
    }
    const vector_4 operator/(const real32& num, const vector_4& vec) {
        return num / vec.data;
    }
    bool operator==(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data == vec_b.data;
    }
    bool operator!=(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data != vec_b.data;
    }
    // Scalar product
    const real32 operator*(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data * vec_b.data;
    }
    std::istream& operator>>(std::istream& in_stream, vector_4& vec) {
        in_stream >> vec.data;
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const vector_4& vec) {
        out_stream << vec.data;
        return out_stream;
    }
}
