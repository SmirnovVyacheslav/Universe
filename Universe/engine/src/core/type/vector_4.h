// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/type/std.h"
#include "src/core/type/vector.h"


namespace engine
{
    union vector_4
    {
        vector<4> data;
        struct
        {
            real32 x;
            real32 y;
            real32 z;
            real32 w;
        };

        vector_4();
        vector_4(real32 x, real32 y, real32 z, real32 w);
        vector_4(vector<4> vec);
        vector_4(vector_4&& src) = default;
        vector_4(const vector_4& src) = default;

        vector_4& operator=(vector_4&& src) = default;
        vector_4& operator=(const vector_4& src) = default;
        real32& operator[](const int32 index);
        const real32& operator[](const int32 index) const;

        ~vector_4() = default;
    };


    const real32 length(const vector_4& vec);
    const vector_4 normalize(const vector_4& vec);
    const vector_4 operator+(const vector_4& vec_a, const vector_4& vec_b);
    const vector_4 operator-(const vector_4& vec_a, const vector_4& vec_b);
    const vector_4 operator+(const vector_4& vec, const real32& num);
    const vector_4 operator-(const vector_4& vec, const real32& num);
    const vector_4 operator*(const vector_4& vec, const real32& num);
    const vector_4 operator/(const vector_4& vec, const real32& num);
    const vector_4 operator+(const real32& num, const vector_4& vec);
    const vector_4 operator-(const real32& num, const vector_4& vec);
    const vector_4 operator*(const real32& num, const vector_4& vec);
    const vector_4 operator/(const real32& num, const vector_4& vec);
    bool operator==(const vector_4& vec_a, const vector_4& vec_b);
    bool operator!=(const vector_4& vec_a, const vector_4& vec_b);
    // Scalar product
    const real32 operator*(const vector_4& vec_a, const vector_4& vec_b);
    std::istream& operator>>(std::istream& in_stream, vector_4& vec);
    std::ostream& operator<<(std::ostream& out_stream, const vector_4& vec);
}
