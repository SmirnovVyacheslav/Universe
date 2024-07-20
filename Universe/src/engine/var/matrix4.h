// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_matrix4.h"


#ifndef ENGINE_MATRIX4
#define ENGINE_MATRIX4

namespace engine
{
   union matrix4
   {
       vector4 data[4];
       struct {
           vector4 row_1;
           vector4 row_2;
           vector4 row_3;
           vector4 row_4;
       };

       matrix4();
       matrix4(vector4 row_1, vector4 row_2, vector4 row_3, vector4 row_4);
       matrix4(matrix4&& src) = default;
       matrix4(const matrix4& src) = default;

       matrix4& operator=(matrix4&& src) = default;
       matrix4& operator=(const matrix4& src) = default;
       vector4& operator[](const int32 index);
       const vector4& operator[](const int32 index) const;

       ~matrix4() = default;
   };


   const matrix4 matrix_identity();
   const matrix4 matrix_look_at(const vector3& eye, const vector3& target, const vector3& up);
   const matrix4 matrix_projection(const fp32 aspect_ratio);
   const matrix4 matrix_rotation_x(const fp32 angle);
   const matrix4 matrix_rotation_y(const fp32 angle);
   const matrix4 matrix_rotation_z(const fp32 angle);
   const matrix4 matrix_transpose(const matrix4& src);
}

#endif
