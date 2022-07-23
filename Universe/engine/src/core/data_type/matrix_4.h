// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "vector_3.h"
#include "vector_4.h"


namespace engine {
    union matrix_4 {
        vector_4 data[4];
        struct {
            vector_4 row_1;
            vector_4 row_2;
            vector_4 row_3;
            vector_4 row_4;
        };

        matrix_4();
        matrix_4(vector_4 row_1, vector_4 row_2, vector_4 row_3, vector_4 row_4);
        ~matrix_4() = default;
        matrix_4(matrix_4&& src) = default;
        matrix_4(const matrix_4& src) = default;

        matrix_4& operator=(matrix_4&& src) = default;
        matrix_4& operator=(const matrix_4& src) = default;
        vector_4& operator[](const int_32 index);
        const vector_4& operator[](const int_32 index) const;
    };
    const matrix_4 matrix_identity();
    const matrix_4 matrix_look_at(const vector_3& eye, const vector_3& target, const vector_3& up);
    const matrix_4 matrix_projection(const real_32 aspect_ratio);
    const matrix_4 matrix_rotation_x(const real_32 angle);
    const matrix_4 matrix_rotation_y(const real_32 angle);
    const matrix_4 matrix_rotation_z(const real_32 angle);
    const matrix_4 matrix_transpose(const matrix_4& src);
}
