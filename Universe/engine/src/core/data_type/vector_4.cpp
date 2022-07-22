// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "vector_4.h"


namespace engine {
    vector_4::vector_4() {
    }
    vector_4::vector_4(real_32 x, real_32 y, real_32 z, real_32 w) : x(x), y(y), z(z), w(w) {
    }
    vector_4::vector_4(const vector<static_cast<uint_32>(4)> vec) {
        data = vec;
    }
    real_32& vector_4::operator[](const int_32 index) {
       return data[index];
    }
    const real_32& vector_4::operator[](const int_32 index) const {
       return data[index];
    }


    const vector_4 operator+(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data + vec_b.data;
    }
    const vector_4 operator-(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data - vec_b.data;
    }
    const vector_4 operator+(const vector_4& vec, const real_32& num) {
        return vec.data + num;
    }
    const vector_4 operator-(const vector_4& vec, const real_32& num) {
        return vec.data - num;
    }
    const vector_4 operator*(const vector_4& vec, const real_32& num) {
        return vec.data * num;
    }
    const vector_4 operator/(const vector_4& vec, const real_32& num) {
        return vec.data / num;
    }
    const vector_4 operator+(const real_32& num, const vector_4& vec) {
        return num + vec.data;
    }
    const vector_4 operator-(const real_32& num, const vector_4& vec) {
        return num - vec.data;
    }
    const vector_4 operator*(const real_32& num, const vector_4& vec) {
        return num * vec.data;
    }
    const vector_4 operator/(const real_32& num, const vector_4& vec) {
        return num / vec.data;
    }
    bool operator==(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data == vec_b.data;
    }
    bool operator!=(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data != vec_b.data;
    }
    // Scalar product
    const real_32 operator*(const vector_4& vec_a, const vector_4& vec_b) {
        return vec_a.data * vec_b.data;
    }


    const real_32 length(const vector_4& vec) {
        return length(vec.data);
    }
    const vector_4 normalize(const vector_4& vec) {
        return normalize(vec.data);
    }
}
