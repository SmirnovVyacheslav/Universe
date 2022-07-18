// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/vector.h"


namespace engine {
    union vector_3_tmp {
        vector<static_cast<uint_32>(3)> data;
        struct {
            real_32 x;
            real_32 y;
            real_32 z;
        };

        vector_3_tmp() = default;
        vector_3_tmp(real_32 x, real_32 y, real_32 z);
        vector_3_tmp(vector<static_cast<uint_32>(3)> vec);
        ~vector_3_tmp() = default;
        vector_3_tmp(vector_3_tmp&& src) = default;
        vector_3_tmp(const vector_3_tmp& src) = default;

        vector_3_tmp& operator=(vector_3_tmp&& src) = default;
        vector_3_tmp& operator=(const vector_3_tmp& src) = default;
        real_32& operator[](const int_32 index);
        const real_32& operator[](const int_32 index) const;
    };
    const vector_3_tmp operator+(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b);
    const vector_3_tmp operator-(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b);
    const vector_3_tmp operator+(const vector_3_tmp& vec, const real_32& num);
    const vector_3_tmp operator-(const vector_3_tmp& vec, const real_32& num);
    const vector_3_tmp operator*(const vector_3_tmp& vec, const real_32& num);
    const vector_3_tmp operator/(const vector_3_tmp& vec, const real_32& num);
    const vector_3_tmp operator+(const real_32& num, const vector_3_tmp& vec);
    const vector_3_tmp operator-(const real_32& num, const vector_3_tmp& vec);
    const vector_3_tmp operator*(const real_32& num, const vector_3_tmp& vec);
    const vector_3_tmp operator/(const real_32& num, const vector_3_tmp& vec);
    bool operator==(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b);
    bool operator!=(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b);
    // Scalar product
    const real_32 operator*(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b);
    // Vector product
    const vector_3_tmp operator^(const vector_3_tmp& vec_a, const vector_3_tmp& vec_b);
}
