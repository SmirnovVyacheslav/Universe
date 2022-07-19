// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "vector_4.h"


namespace engine {
    vector_4_tmp::vector_4_tmp(real_32 x, real_32 y, real_32 z, real_32 w) : x(x), y(y), z(z), w(w) {
    }
    vector_4_tmp::vector_4_tmp(const vector<static_cast<uint_32>(4)> vec) {
        data = vec;
    }
    real_32& vector_4_tmp::operator[](const int_32 index) {
       return data[index];
    }
    const real_32& vector_4_tmp::operator[](const int_32 index) const {
       return data[index];
    }


    const vector_4_tmp operator+(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b) {
        return vec_a.data + vec_b.data;
    }
    const vector_4_tmp operator-(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b) {
        return vec_a.data - vec_b.data;
    }
    const vector_4_tmp operator+(const vector_4_tmp& vec, const real_32& num) {
        return vec.data + num;
    }
    const vector_4_tmp operator-(const vector_4_tmp& vec, const real_32& num) {
        return vec.data - num;
    }
    const vector_4_tmp operator*(const vector_4_tmp& vec, const real_32& num) {
        return vec.data * num;
    }
    const vector_4_tmp operator/(const vector_4_tmp& vec, const real_32& num) {
        return vec.data / num;
    }
    const vector_4_tmp operator+(const real_32& num, const vector_4_tmp& vec) {
        return num + vec.data;
    }
    const vector_4_tmp operator-(const real_32& num, const vector_4_tmp& vec) {
        return num - vec.data;
    }
    const vector_4_tmp operator*(const real_32& num, const vector_4_tmp& vec) {
        return num * vec.data;
    }
    const vector_4_tmp operator/(const real_32& num, const vector_4_tmp& vec) {
        return num / vec.data;
    }
    bool operator==(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b) {
        return vec_a.data == vec_b.data;
    }
    bool operator!=(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b) {
        return vec_a.data != vec_b.data;
    }
    // Scalar product
    const real_32 operator*(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b) {
        return vec_a.data * vec_b.data;
    }


    const real_32 length(const vector_4_tmp& vec) {
        return length(vec.data);
    }
    const vector_4_tmp normalize(const vector_4_tmp& vec) {
        return normalize(vec.data);
    }
}
