// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_vector4.h"


#ifndef ENGINE_VECTOR4
#define ENGINE_VECTOR4

namespace engine
{
    union vector4
    {
        vector<4> data;
        struct
        {
            fp32 x;
            fp32 y;
            fp32 z;
            fp32 w;
        };

        vector4();
        vector4(fp32 x, fp32 y, fp32 z, fp32 w);
        vector4(vector<4> vec);
        vector4(vector4&& src) = default;
        vector4(const vector4& src) = default;

        operator const fp32* () const;
        vector4& operator=(vector4&& src) = default;
        vector4& operator=(const vector4& src) = default;
        fp32& operator[](const int32 index);
        const fp32& operator[](const int32 index) const;

        ~vector4() = default;
    };


    const fp32 length(const vector4& vec);
    const vector4 normalize(const vector4& vec);
    const vector4 operator+(const vector4& vec_a, const vector4& vec_b);
    const vector4 operator-(const vector4& vec_a, const vector4& vec_b);
    const vector4 operator+(const vector4& vec, const fp32& num);
    const vector4 operator-(const vector4& vec, const fp32& num);
    const vector4 operator*(const vector4& vec, const fp32& num);
    const vector4 operator/(const vector4& vec, const fp32& num);
    const vector4 operator+(const fp32& num, const vector4& vec);
    const vector4 operator-(const fp32& num, const vector4& vec);
    const vector4 operator*(const fp32& num, const vector4& vec);
    const vector4 operator/(const fp32& num, const vector4& vec);
    bool operator==(const vector4& vec_a, const vector4& vec_b);
    bool operator!=(const vector4& vec_a, const vector4& vec_b);
    // Scalar product
    const fp32 operator*(const vector4& vec_a, const vector4& vec_b);
    std::istream& operator>>(std::istream& in_stream, vector4& vec);
    std::ostream& operator<<(std::ostream& out_stream, const vector4& vec);
}

#endif
