//// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
//#pragma once
//#include "src/core/type/std.h"
//#include "src/core/type/vector.h"
//
//
//namespace engine
//{
//    union vector4
//    {
//        vector<4> data;
//        struct
//        {
//            real32 x;
//            real32 y;
//            real32 z;
//            real32 w;
//        };
//
//        vector4();
//        vector4(real32 x, real32 y, real32 z, real32 w);
//        vector4(vector<4> vec);
//        vector4(vector4&& src) = default;
//        vector4(const vector4& src) = default;
//
//        operator const real32* () const;
//        vector4& operator=(vector4&& src) = default;
//        vector4& operator=(const vector4& src) = default;
//        real32& operator[](const int32 index);
//        const real32& operator[](const int32 index) const;
//
//        ~vector4() = default;
//    };
//
//
//    const real32 length(const vector4& vec);
//    const vector4 normalize(const vector4& vec);
//    const vector4 operator+(const vector4& vec_a, const vector4& vec_b);
//    const vector4 operator-(const vector4& vec_a, const vector4& vec_b);
//    const vector4 operator+(const vector4& vec, const real32& num);
//    const vector4 operator-(const vector4& vec, const real32& num);
//    const vector4 operator*(const vector4& vec, const real32& num);
//    const vector4 operator/(const vector4& vec, const real32& num);
//    const vector4 operator+(const real32& num, const vector4& vec);
//    const vector4 operator-(const real32& num, const vector4& vec);
//    const vector4 operator*(const real32& num, const vector4& vec);
//    const vector4 operator/(const real32& num, const vector4& vec);
//    bool operator==(const vector4& vec_a, const vector4& vec_b);
//    bool operator!=(const vector4& vec_a, const vector4& vec_b);
//    // Scalar product
//    const real32 operator*(const vector4& vec_a, const vector4& vec_b);
//    std::istream& operator>>(std::istream& in_stream, vector4& vec);
//    std::ostream& operator<<(std::ostream& out_stream, const vector4& vec);
//}
