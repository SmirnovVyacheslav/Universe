// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "vector_3.h"


namespace engine {
    vector_3_tmp::vector_3_tmp(real_32 x, real_32 y, real_32 z) : x(x), y(y), z(z) {
    }
    vector_3_tmp::vector_3_tmp(const vector<static_cast<uint_32>(3)> vec) {
        data = vec;
    }
    real_32& vector_3_tmp::operator[](const int_32 index) {
        return data[index];
    }
    const real_32& vector_3_tmp::operator[](const int_32 index) const {
        return data[index];
    }


    const vector_3_tmp operator+(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b) {
        return vec_a.data + vec_b.data;
    }
    const vector_3_tmp operator-(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b) {
        return vec_a.data - vec_b.data;
    }
    const vector_3_tmp operator+(const vector_3_tmp& vec, const real_32& num) {
        return vec.data + num;
    }
    const vector_3_tmp operator-(const vector_3_tmp& vec, const real_32& num) {
        return vec.data - num;
    }
    const vector_3_tmp operator*(const vector_3_tmp& vec, const real_32& num) {
        return vec.data * num;
    }
    const vector_3_tmp operator/(const vector_3_tmp& vec, const real_32& num) {
        return vec.data / num;
    }
    const vector_3_tmp operator+(const real_32& num, const vector_3_tmp& vec) {
        return num + vec.data;
    }
    const vector_3_tmp operator-(const real_32& num, const vector_3_tmp& vec) {
        return num - vec.data;
    }
    const vector_3_tmp operator*(const real_32& num, const vector_3_tmp& vec) {
        return num * vec.data;
    }
    const vector_3_tmp operator/(const real_32& num, const vector_3_tmp& vec) {
        return num / vec.data;
    }
    bool operator==(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b) {
        return vec_a.data == vec_b.data;
    }
    bool operator!=(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b) {
        return vec_a.data != vec_b.data;
    }
    // Scalar product
    const real_32 operator*(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b) {
        return vec_a.data * vec_b.data;
    }
    // Vector product
    const vector_3_tmp operator^(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b) {
        return { vec_a.y * vec_b.z - vec_a.z * vec_b.y,
                 vec_a.z * vec_b.x - vec_a.x * vec_b.z,
                 vec_a.x * vec_b.y - vec_a.y * vec_b.x };
    }


    const real_32 length(const vector_3_tmp& vec) {
        return length(vec.data);
    }
    const vector_3_tmp normalize(const vector_3_tmp& vec) {
        return normalize(vec.data);
    }
}
