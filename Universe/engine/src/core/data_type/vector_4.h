// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/vector.h"


namespace engine {
    union vector_4 {
        vector<static_cast<uint_32>(4)> data;
        struct {
            real_32 x;
            real_32 y;
            real_32 z;
            real_32 w;
        };

        vector_4();
        vector_4(real_32 x, real_32 y, real_32 z, real_32 w);
        vector_4(vector<static_cast<uint_32>(4)> vec);
        ~vector_4() = default;
        vector_4(vector_4&& src) = default;
        vector_4(const vector_4& src) = default;

        vector_4& operator=(vector_4&& src) = default;
        vector_4& operator=(const vector_4& src) = default;
        real_32& operator[](const int_32 index);
        const real_32& operator[](const int_32 index) const;
    };
    const vector_4 operator+(const vector_4& vec_a, const vector_4& vec_b);
    const vector_4 operator-(const vector_4& vec_a, const vector_4& vec_b);
    const vector_4 operator+(const vector_4& vec, const real_32& num);
    const vector_4 operator-(const vector_4& vec, const real_32& num);
    const vector_4 operator*(const vector_4& vec, const real_32& num);
    const vector_4 operator/(const vector_4& vec, const real_32& num);
    const vector_4 operator+(const real_32& num, const vector_4& vec);
    const vector_4 operator-(const real_32& num, const vector_4& vec);
    const vector_4 operator*(const real_32& num, const vector_4& vec);
    const vector_4 operator/(const real_32& num, const vector_4& vec);
    bool operator==(const vector_4& vec_a, const vector_4& vec_b);
    bool operator!=(const vector_4& vec_a, const vector_4& vec_b);
    // Scalar product
    const real_32 operator*(const vector_4& vec_a, const vector_4& vec_b);
    const real_32 length(const vector_4& vec);
    const vector_4 normalize(const vector_4& vec);
}
