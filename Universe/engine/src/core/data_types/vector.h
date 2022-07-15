// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/math/const.h"


namespace engine {
    template <uint_32 size>
    struct vector;
    union vector_3;
    union vector_4;


    template <uint_32 size>
    using vector = struct vector;
    using vector_3 = union vector_3;
    using vector_4 = union vector_4;


    template <uint_32 size>
    struct vector {
        real_32[size] data;

        vector();
        ~vector() = default;
        vector(vector&& src) = default;
        vector(const vector& src) = default;

        vector& operator=(vector&& src) = default;
        vector& operator=(const vector& src) = default;
        real_32& operator[](const int_32 index);

    private:
        template <uint_32 size>
        const vector<size> calculate_operation(
            const vector<size>& vec_a,
            const vector<size>& vec_b,
            const std::function<const real_32(const real_32, const real_32)> operation) {
            vector<size> vec_res;
            for (uint_32 i = 0; i < size; ++i) {
                vec_res[i] = operation(vec_a[i], vec_b[i]);
            }
            return vec_res;
        }
    };
    union vector_3 {
        vector<static_cast<uint_32>(3)> data;
        struct {
            real_32 x;
            real_32 y;
            real_32 z;
        };

        vector_3() = default;
        vector_3(real_32 x, real_32 y, real_32 z);
        ~vector_3() = default;
        vector_3(vector_3&& src) = default;
        vector_3(const vector_3& src) = default;

        vector_3& operator=(vector_3&& src) = default;
        vector_3& operator=(const vector_3& src) = default;
        real_32& operator[](const int_32 index);


    };
    union vector_4 {
        vector<static_cast<uint_32>(4)> data;
        struct {
            real_32 x;
            real_32 y;
            real_32 z;
            real_32 w;
        };

        vector_4() = default;
        vector_4(real_32 x, real_32 y, real_32 z, real_32 w);
        ~vector_4() = default;
        vector_4(vector_4&& src) = default;
        vector_4(const vector_4& src) = default;

        vector_4& operator=(vector_4&& src) = default;
        vector_4& operator=(const vector_4& src) = default;
        real_32& operator[](const int_32 index);
    };


    template <uint_32 size>
    vector<size>::vector() {
        for (uint_32 i = 0; i < size; ++i) {
            data[i] = 0.0f;
        }
    }
    template <uint_32 size>
    real_32& vector<size>::operator[](const int_32 index) {
        int_32 size_int_32 = static_cast<int_32>(size);
        return data[(size_int_32 + index % size_int_32) % size_int_32];
    }


    vector_3::vector_3(real_32 x, real_32 y, real_32 z) : x(x), y(y), z(z) {
    }
    real_32& vector_3::operator[](const int_32 index) {
        return data[index];
    }


    vector_4::vector_4(real_32 x, real_32 y, real_32 z, real_32 w) : x(x), y(y), z(z), w(w) {
    }
    real_32& vector_4::operator[](const int_32 index) {
        return data[index];
    }


    template <uint_32 size>
    vector<size> operator+(const vector<size>& vec_a, const vector<size>& vec_b) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = vec_a[i] + vec_b[i];
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator-(const vector<size>& vec_a, const vector<size>& vec_b) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = vec_a[i] - vec_b[i];
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator+(const vector<size>& vec, const real_32& num) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = vec[i] + num;
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator-(const vector<size>& vec, const real_32& num) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = vec[i] - num;
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator*(const vector<size>& vec, const real_32& num) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = vec[i] * num;
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator/(const vector<size>& vec, const real_32& num) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = vec[i] / num;
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator+(const real_32& num, const vector<size>& vec) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = num + vec[i];
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator-(const real_32& num, const vector<size>& vec) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = num - vec[i];
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator*(const real_32& num, const vector<size>& vec) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = num * vec[i];
        }
        return vec_res;
    }
    template <uint_32 size>
    vector<size> operator/(const real_32& num, const vector<size>& vec) {
        vector<size> vec_res;
        for (uint_32 i = 0; i < size; ++i) {
            vec_res[i] = num / vec[i];
        }
        return vec_res;
    }
    template <uint_32 size>
    bool operator==(const vector<size>& vec_a, const vector<size>& vec_b) {
        for (uint_32 i = 0; i < size; ++i) {
            if ((vec_a[i] - vec_b[i]) * (vec_a[i] - vec_b[i]) > eps) {
                return false;
            }
        }
        return true;
    }
    template <uint_32 size>
    bool operator!=(const vector<size>& vec_a, const vector<size>& vec_b) {
        return !(vec_a == vec_b);
    }
    template <uint_32 size>
    real_32 operator*(const vector<size>& vec_a, const vector<size>& vec_b);
    template <uint_32 size>
    vector_3 operator^(const vector<size>& vec_a, const vector<size>& vec_b);


}
