// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_vector3.h"


#ifndef ENGINE_VECTOR3
#define ENGINE_VECTOR3

namespace engine
{
    union vector3
    {
        vector<3> data;
        struct
        {
            fp32 x;
            fp32 y;
            fp32 z;
        };

        vector3();
        vector3(fp32 x, fp32 y, fp32 z);
        vector3(vector<3> vec);
        vector3(vector3&& src) = default;
        vector3(const vector3& src) = default;

        operator const fp32* () const;
        vector3& operator=(vector3&& src) = default;
        vector3& operator=(const vector3& src) = default;
        fp32& operator[](const int32 index);
        const fp32& operator[](const int32 index) const;

        ~vector3() = default;
    };


    const fp32 length(const vector3& vec);
    const vector3 normalize(const vector3& vec);
    const vector3 operator+(const vector3& vec_a, const vector3& vec_b);
    const vector3 operator-(const vector3& vec_a, const vector3& vec_b);
    const vector3 operator+(const vector3& vec, const fp32& num);
    const vector3 operator-(const vector3& vec, const fp32& num);
    const vector3 operator*(const vector3& vec, const fp32& num);
    const vector3 operator/(const vector3& vec, const fp32& num);
    const vector3 operator+(const fp32& num, const vector3& vec);
    const vector3 operator-(const fp32& num, const vector3& vec);
    const vector3 operator*(const fp32& num, const vector3& vec);
    const vector3 operator/(const fp32& num, const vector3& vec);
    bool operator==(const vector3& vec_a, const vector3& vec_b);
    bool operator!=(const vector3& vec_a, const vector3& vec_b);
    // Scalar product
    const fp32 operator*(const vector3& vec_a, const vector3& vec_b);
    // Vector product
    const vector3 operator^(const vector3& vec_a, const vector3& vec_b);
    std::istream& operator>>(std::istream& in_stream, vector3& vec);
    std::ostream& operator<<(std::ostream& out_stream, const vector3& vec);
}

#endif
