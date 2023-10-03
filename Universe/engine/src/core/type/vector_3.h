// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "std.h"
#include "vector.h"


namespace engine {
    union vector_3 {
        vector<3> data;
        struct {
            real32 x;
            real32 y;
            real32 z;
        };

        vector_3();
        vector_3(real32 x, real32 y, real32 z);
        vector_3(vector<3> vec);
        vector_3(vector_3&& src) = default;
        vector_3(const vector_3& src) = default;

        vector_3& operator=(vector_3&& src) = default;
        vector_3& operator=(const vector_3& src) = default;
        real32& operator[](const int32 index);
        const real32& operator[](const int32 index) const;

        ~vector_3() = default;
    };


    const real32 length(const vector_3& vec);
    const vector_3 normalize(const vector_3& vec);
    const vector_3 operator+(const vector_3& vec_a, const vector_3& vec_b);
    const vector_3 operator-(const vector_3& vec_a, const vector_3& vec_b);
    const vector_3 operator+(const vector_3& vec, const real32& num);
    const vector_3 operator-(const vector_3& vec, const real32& num);
    const vector_3 operator*(const vector_3& vec, const real32& num);
    const vector_3 operator/(const vector_3& vec, const real32& num);
    const vector_3 operator+(const real32& num, const vector_3& vec);
    const vector_3 operator-(const real32& num, const vector_3& vec);
    const vector_3 operator*(const real32& num, const vector_3& vec);
    const vector_3 operator/(const real32& num, const vector_3& vec);
    bool operator==(const vector_3& vec_a, const vector_3& vec_b);
    bool operator!=(const vector_3& vec_a, const vector_3& vec_b);
    // Scalar product
    const real32 operator*(const vector_3& vec_a, const vector_3& vec_b);
    // Vector product
    const vector_3 operator^(const vector_3& vec_a, const vector_3& vec_b);
    std::istream& operator>>(std::istream& in_stream, vector_3& vec);
    std::ostream& operator<<(std::ostream& out_stream, const vector_3& vec);
}
