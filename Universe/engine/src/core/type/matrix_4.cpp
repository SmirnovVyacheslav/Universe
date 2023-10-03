// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "matrix_4.h"


namespace engine {
    const int32 matrix_size = 4;
    const real32 fov_angle_y = 1.570796327f;
    const real32 projection_front_z = 0.01f;
    const real32 projection_back_z = 100.0f;


    matrix_4::matrix_4() :
        row_1({ 0.0f, 0.0f, 0.0f, 0.0f }),
        row_2({ 0.0f, 0.0f, 0.0f, 0.0f }),
        row_3({ 0.0f, 0.0f, 0.0f, 0.0f }),
        row_4({ 0.0f, 0.0f, 0.0f, 0.0f }) {
    }
    matrix_4::matrix_4(vector_4 row_1, vector_4 row_2, vector_4 row_3, vector_4 row_4) :
        row_1(row_1), row_2(row_2), row_3(row_3), row_4(row_4) {
    }
    vector_4& matrix_4::operator[](const int32 index) {
        return data[(matrix_size + index % matrix_size) % matrix_size];
    }
    const vector_4& matrix_4::operator[](const int32 index) const {
        return data[(matrix_size + index % matrix_size) % matrix_size];
    }


    const matrix_4 matrix_identity() {
        return {
            vector_4(1.0f, 0.0f, 0.0f, 0.0f),
            vector_4(0.0f, 1.0f, 0.0f, 0.0f),
            vector_4(0.0f, 0.0f, 1.0f, 0.0f),
            vector_4(0.0f, 0.0f, 0.0f, 1.0f)
        };
    }
    const matrix_4 matrix_look_at(const vector_3& eye, const vector_3& target, const vector_3& up) {
        vector_3 z_axis = normalize(eye - target);
        vector_3 x_axis = normalize(up ^ z_axis);
        vector_3 y_axis = z_axis ^ x_axis;

        return {
            vector_4(  x_axis.x,        y_axis.x,        z_axis.x,      0.0f),
            vector_4(  x_axis.y,        y_axis.y,        z_axis.y,      0.0f),
            vector_4(  x_axis.z,        y_axis.z,        z_axis.z,      0.0f),
            vector_4(-(x_axis * eye), -(y_axis * eye), -(z_axis * eye), 1.0f)
        };
    }
    const matrix_4 matrix_projection(const real32 aspect_ratio) {
        real32 fov_sin = sinf(0.5f * fov_angle_y);
        real32 fov_cos = cosf(0.5f * fov_angle_y);

        real32 height = fov_cos / fov_sin;
        real32 width = height / aspect_ratio;
        real32 projection_ratio = projection_back_z / (projection_front_z - projection_back_z);

        return {
            vector_4(width, 0.0f,   0.0f,                                  0.0f),
            vector_4(0.0f,  height, 0.0f,                                  0.0f),
            vector_4(0.0f,  0.0f,   projection_ratio,                     -1.0f),
            vector_4(0.0f,  0.0f,   projection_ratio * projection_front_z, 0.0f)
        };
    }
    const matrix_4 matrix_rotation_x(const real32 angle) {
        real32 sin_angle = sinf(angle);
        real32 cos_angle = cosf(angle);

        return {
            vector_4(1.0f, 0.0f,       0.0f,      0.0f),
            vector_4(0.0f, cos_angle, -sin_angle, 0.0f),
            vector_4(0.0f, sin_angle,  cos_angle, 0.0f),
            vector_4(0.0f, 0.0f,       0.0f,      1.0f)
        };
    }
    const matrix_4 matrix_rotation_y(const real32 angle) {
        real32 sin_angle = sinf(angle);
        real32 cos_angle = cosf(angle);

        return {
            vector_4(cos_angle,  0.0f, sin_angle, 0.0f),
            vector_4(0.0f,       1.0f, 0.0f,      0.0f),
            vector_4(-sin_angle, 0.0f, cos_angle, 0.0f),
            vector_4(0.0f,       0.0f, 0.0f,      1.0f)
        };
    }
    const matrix_4 matrix_rotation_z(const real32 angle) {
        real32 sin_angle = sinf(angle);
        real32 cos_angle = cosf(angle);

        return {
            vector_4(cos_angle, -sin_angle, 0.0f, 0.0f),
            vector_4(sin_angle,  cos_angle, 0.0f, 0.0f),
            vector_4(0.0f,       0.0f,      1.0f, 0.0f),
            vector_4(0.0f,       0.0f,      0.0f, 1.0f)
        };
    }
    const matrix_4 matrix_transpose(const matrix_4& src) {
        vector_4 row_1 = src.row_1;
        vector_4 row_2 = src.row_2;
        vector_4 row_3 = src.row_3;
        vector_4 row_4 = src.row_4;

        return {
            vector_4(row_1.x, row_2.x, row_3.x, row_4.x),
            vector_4(row_1.y, row_2.y, row_3.y, row_4.y),
            vector_4(row_1.z, row_2.z, row_3.z, row_4.z),
            vector_4(row_1.w, row_2.w, row_3.w, row_4.w)
        };
    }
}
