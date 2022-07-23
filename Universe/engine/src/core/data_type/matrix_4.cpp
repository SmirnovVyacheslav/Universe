// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "matrix_4.h"


namespace engine {
    const int_32 matrix_size = 4;
    const real_32 fov_angle_x = 1.570796327f;
    const real_32 fov_angle_y = 0.872665f;
    const real_32 projection_front_z = 0.01f;
    const real_32 projection_back_z = 100.0f;


    matrix_4::matrix_4() {
    }
    matrix_4::matrix_4(vector_4 row_1, vector_4 row_2, vector_4 row_3, vector_4 row_4) :
        row_1(row_1), row_2(row_2), row_3(row_3), row_4(row_4) {
    }
    vector_4& matrix_4::operator[](const int_32 index) {
        return data[(matrix_size + index % matrix_size) % matrix_size];
    }
    const vector_4& matrix_4::operator[](const int_32 index) const {
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
    //const matrix_4 matrix_projection() {
    //    

    //    /*data[0] = vector_4(atanf(fov_angle_x * 0.5f), 0.0f, 0.0f, 0.0f);
    //    data[1] = vector_4(0.0f, atanf(fov_angle_y * 0.5), 0.0f, 0.0f);
    //    data[2] = vector_4(0.0f, 0.0f, projection_back_z + projection_front_z / (near_z - far_z), -1.0f);
    //    data[3] = vector_4(0.0f, 0.0f, -1.0f, 0.0f);*/
    //}
    //const matrix_4 matrix_rotation_x(const real_32 angle);
    //const matrix_4 matrix_rotation_y(const real_32 angle);
    //const matrix_4 matrix_rotation_z(const real_32 angle);
    //const matrix_4 matrix_transpose(const matrix_4& src);

   /* void projection(float aspect_ratio) {
        float fov_angle_y = 1.570796327f;
        float near_z = 0.01f;
        float far_z = 100.0f;

        float fov_sin = sinf(0.5f * fov_angle_y);
        float fov_cos = cosf(0.5f * fov_angle_y);

        float height = fov_cos / fov_sin;
        float width = height / aspect_ratio;

        data[0] = vector_4(width, 0.0f, 0.0f, 0.0f);
        data[1] = vector_4(0.0f, height, 0.0f, 0.0f);
        data[2] = vector_4(0.0f, 0.0f, far_z / (near_z - far_z), -1.0f);
        data[3] = vector_4(0.0f, 0.0f, data[2].z * near_z, 0.0f);
    }
    void rotation_y(float angle) {
        float sin_angle = sinf(angle);
        float cos_angle = cosf(angle);

        data[0] = vector_4(cos_angle, 0.0f, sin_angle, 0.0f);
        data[1] = vector_4(0.0f, 1.0f, 0.0f, 0.0f);
        data[2] = vector_4(-sin_angle, 0.0f, cos_angle, 0.0f);
        data[3] = vector_4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    void transpose() {
        vector_4 row_0 = data[0];
        vector_4 row_1 = data[1];
        vector_4 row_2 = data[2];
        vector_4 row_3 = data[3];

        data[0] = vector_4(row_0.x, row_1.x, row_2.x, row_3.x);
        data[1] = vector_4(row_0.y, row_1.y, row_2.y, row_3.y);
        data[2] = vector_4(row_0.z, row_1.z, row_2.z, row_3.z);
        data[3] = vector_4(row_0.w, row_1.w, row_2.w, row_3.w);
    }*/
}
