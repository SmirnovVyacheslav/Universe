// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef MATH_H
#define MATH_H


namespace engine
{
    const float eps = 0.00000001f;
    const float pi = 3.14159265358979323846f;

    using vector_3 = struct vector_3;
    using vector_4 = struct vector_4;

    float factorial(int n);
    float radian_to_degree(float radian);
    float degree_to_radian(float degree);

    vector_3 project_vector_to_plane(vector_3 vector_to_project, vector_3 plane_point, vector_3 plane_normal);
    // vector_3 rotate_vector(vector_3 vector, vector_3 axis, float angle);


    struct vector_3
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        vector_3() {};
        vector_3(float x, float y, float z) : x(x), y(y), z(z) {};
        vector_3(const vector_3& vec) = default;

        bool is_zero();
         float length();
         vector_3& normalize();
        vector_3& trunc();

        vector_3& operator=(const vector_3& vec);

        vector_3& operator+=(const float& num);
        vector_3& operator-=(const float& num);
        vector_3& operator*=(const float& num);
        vector_3& operator/=(const float& num);
        vector_3& operator+=(const vector_3& vec);
        vector_3& operator-=(const vector_3& vec);
        vector_3& operator*=(const vector_3& vec);
        vector_3& operator/=(const vector_3& vec);
        /**
         * Scalar dot product
         * a = (x1, y1, z1); b = (x2, y2, z2)
         * a & b =
         * x1 * x2 + y1 * y2 + z1 * z2
         */
        float operator&=(const vector_3& vec);
        /**
         * Vector cross product
         * a = (x1, y1, z1); b = (x2, y2, z2)
         * a ^ b =
         * (y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2)
         */
        vector_3& operator^=(const vector_3& vec);

        operator vector_4();
    };

    vector_3 operator+(const vector_3& vec_a, const vector_3& vec_b);
    vector_3 operator-(const vector_3& vec_a, const vector_3& vec_b);
    vector_3 operator*(const vector_3& vec_a, const vector_3& vec_b);
    vector_3 operator/(const vector_3& vec_a, const vector_3& vec_b);

    float operator&(const vector_3& vec_a, const vector_3& vec_b);
    vector_3 operator^(const vector_3& vec_a, const vector_3& vec_b);

    bool operator==(const vector_3& vec_a, const vector_3& vec_b);
    bool operator!=(const vector_3& vec_a, const vector_3& vec_b);

    vector_3 operator+(const float& num, const vector_3& vec);
    vector_3 operator-(const float& num, const vector_3& vec);
    vector_3 operator*(const float& num, const vector_3& vec);
    vector_3 operator/(const float& num, const vector_3& vec);
    vector_3 operator+(const vector_3& vec, const float& num);
    vector_3 operator-(const vector_3& vec, const float& num);
    vector_3 operator*(const vector_3& vec, const float& num);
    vector_3 operator/(const vector_3& vec, const float& num);

    // float distance(vector_3 vec_a, vector_3 vec_b);
    // float distance(vector_3 vec_a, vector_4 vec_b);
    // float distance(vector_4 vec_a, vector_3 vec_b);
    // float distance(vector_4 vec_a, vector_4 vec_b);

    // float angle(vector_3 vec_a, vector_3 vec_b);


    struct vector_4
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        vector_4() {};
        vector_4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
        vector_4(const vector_4& vec) = default;

         float length();
         vector_4& normalize();
        vector_4& trunc();

        vector_4& operator= (const vector_4& vec);

        vector_4& operator+=(const float& num);
        vector_4& operator-=(const float& num);
        vector_4& operator*=(const float& num);
        vector_4& operator/=(const float& num);
        vector_4& operator+=(const vector_4& vec);
        vector_4& operator-=(const vector_4& vec);
        vector_4& operator*=(const vector_4& vec);
        vector_4& operator/=(const vector_4& vec);

        operator vector_3();
    };

    vector_4 operator+(const vector_4& vec_a, const vector_4& vec_b);
    vector_4 operator-(const vector_4& vec_a, const vector_4& vec_b);
    vector_4 operator*(const vector_4& vec_a, const vector_4& vec_b);
    vector_4 operator/(const vector_4& vec_a, const vector_4& vec_b);

    bool operator==(const vector_4& vec_a, const vector_4& vec_b);
    bool operator!=(const vector_4& vec_a, const vector_4& vec_b);

    vector_4 operator+(const float& num, const vector_4& vec);
    vector_4 operator-(const float& num, const vector_4& vec);
    vector_4 operator*(const float& num, const vector_4& vec);
    vector_4 operator/(const float& num, const vector_4& vec);
    vector_4 operator+(const vector_4& vec, const float& num);
    vector_4 operator-(const vector_4& vec, const float& num);
    vector_4 operator*(const vector_4& vec, const float& num);
    vector_4 operator/(const vector_4& vec, const float& num);
}
#endif
