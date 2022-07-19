// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/vector.h"


namespace engine {
    union vector_4_tmp {
        vector<static_cast<uint_32>(4)> data;
        struct {
            real_32 x;
            real_32 y;
            real_32 z;
            real_32 w;
        };

        vector_4_tmp() = default;
        vector_4_tmp(real_32 x, real_32 y, real_32 z, real_32 w);
        vector_4_tmp(vector<static_cast<uint_32>(4)> vec);
        ~vector_4_tmp() = default;
        vector_4_tmp(vector_4_tmp&& src) = default;
        vector_4_tmp(const vector_4_tmp& src) = default;

        vector_4_tmp& operator=(vector_4_tmp&& src) = default;
        vector_4_tmp& operator=(const vector_4_tmp& src) = default;
        real_32& operator[](const int_32 index);
        const real_32& operator[](const int_32 index) const;
    };
    const vector_4_tmp operator+(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b);
    const vector_4_tmp operator-(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b);
    const vector_4_tmp operator+(const vector_4_tmp& vec, const real_32& num);
    const vector_4_tmp operator-(const vector_4_tmp& vec, const real_32& num);
    const vector_4_tmp operator*(const vector_4_tmp& vec, const real_32& num);
    const vector_4_tmp operator/(const vector_4_tmp& vec, const real_32& num);
    const vector_4_tmp operator+(const real_32& num, const vector_4_tmp& vec);
    const vector_4_tmp operator-(const real_32& num, const vector_4_tmp& vec);
    const vector_4_tmp operator*(const real_32& num, const vector_4_tmp& vec);
    const vector_4_tmp operator/(const real_32& num, const vector_4_tmp& vec);
    bool operator==(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b);
    bool operator!=(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b);
    // Scalar product
    const real_32 operator*(const vector_4_tmp& vec_a, const vector_4_tmp& vec_b);
    const real_32 length(const vector_4_tmp& vec);
    const vector_4_tmp normalize(const vector_4_tmp& vec);
}
