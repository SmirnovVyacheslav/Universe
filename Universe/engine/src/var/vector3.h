//// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
//#pragma once
//#include "src/core/type/std.h"
//#include "src/core/type/vector.h"
//
//
//namespace engine
//{
//    union vector3
//    {
//        vector<3> data;
//        struct
//        {
//            real32 x;
//            real32 y;
//            real32 z;
//        };
//
//        vector3();
//        vector3(real32 x, real32 y, real32 z);
//        vector3(vector<3> vec);
//        vector3(vector3&& src) = default;
//        vector3(const vector3& src) = default;
//
//        operator const real32* () const;
//        vector3& operator=(vector3&& src) = default;
//        vector3& operator=(const vector3& src) = default;
//        real32& operator[](const int32 index);
//        const real32& operator[](const int32 index) const;
//
//        ~vector3() = default;
//    };
//
//
//    const real32 length(const vector3& vec);
//    const vector3 normalize(const vector3& vec);
//    const vector3 operator+(const vector3& vec_a, const vector3& vec_b);
//    const vector3 operator-(const vector3& vec_a, const vector3& vec_b);
//    const vector3 operator+(const vector3& vec, const real32& num);
//    const vector3 operator-(const vector3& vec, const real32& num);
//    const vector3 operator*(const vector3& vec, const real32& num);
//    const vector3 operator/(const vector3& vec, const real32& num);
//    const vector3 operator+(const real32& num, const vector3& vec);
//    const vector3 operator-(const real32& num, const vector3& vec);
//    const vector3 operator*(const real32& num, const vector3& vec);
//    const vector3 operator/(const real32& num, const vector3& vec);
//    bool operator==(const vector3& vec_a, const vector3& vec_b);
//    bool operator!=(const vector3& vec_a, const vector3& vec_b);
//    // Scalar product
//    const real32 operator*(const vector3& vec_a, const vector3& vec_b);
//    // Vector product
//    const vector3 operator^(const vector3& vec_a, const vector3& vec_b);
//    std::istream& operator>>(std::istream& in_stream, vector3& vec);
//    std::ostream& operator<<(std::ostream& out_stream, const vector3& vec);
//}
