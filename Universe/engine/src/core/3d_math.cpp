// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include <math.h>
#include "3d_math.h"


namespace engine
{
    float factorial(int n)
    {
        if (n == 0 || n == 1)
            return 1.0f;

        float result = 1.0f;
        for (int i = 1; i <= n; ++i)
        {
            result *= static_cast<float>(i);
        }
        return result;
    }

    float radian_to_degree(float radian)
    {
        return radian * 180.0f / pi;
    }

    float degree_to_radian(float degree)
    {
        return degree * pi / 180.0f;
    }

    vector_3 project_vector_to_plane(vector_3 vector_to_project, vector_3 plane_point, vector_3 plane_normal)
    {
        // Need to make projection only for vector_end_point
        vector_3 vector_end_point = vector_to_project + plane_point;

        // Make dot projection
        float distance_to_plane = vector_to_project & plane_normal;
        vector_3 plane_point_b = vector_end_point - (distance_to_plane * plane_normal);

        // Construst new projection for vector
        return plane_point_b - plane_point;
    }

    //vector_3 rotate_vector(vector_3 vector, vector_3 axis, float angle)
    //{
    //    angle = degree_to_radian(angle);
    //    // Rotation matrix
    //    std::vector<vector_3> matrix = {
    //        vector_3(cos(angle) + (1 - cos(angle)) * axis.x * axis.x,
    //                 (1 - cos(angle)) * axis.x * axis.y - sin(angle) * axis.z,
    //                 (1 - cos(angle)) * axis.x * axis.z + sin(angle) * axis.y),
    //        vector_3((1 - cos(angle)) * axis.x * axis.y + sin(angle) * axis.z,
    //                 cos(angle) + (1 - cos(angle)) * axis.y * axis.y,
    //                 (1 - cos(angle)) * axis.y * axis.z - sin(angle) * axis.x),
    //        vector_3((1 - cos(angle)) * axis.x * axis.z - sin(angle) * axis.y,
    //                 (1 - cos(angle)) * axis.y * axis.z + sin(angle) * axis.x,
    //                 cos(angle) + (1 - cos(angle)) * axis.z * axis.z)
    //    };

    //    vector_3 result = {
    //        matrix[0] & vector,
    //        matrix[1] & vector,
    //        matrix[2] & vector
    //    };

    //    return result;
    //}

    bool vector_3::is_zero()
    {
        return (x + y + z) < eps;
    }

    float vector_3::length()
    {
        double _x = static_cast<double>(x);
        double _y = static_cast<double>(y);
        double _z = static_cast<double>(z);
        return static_cast<float>(sqrt(_x * _x + _y * _y + _z * _z));
    }

    vector_3& vector_3::normalize()
    {
        float len = length();
        x /= len;
        y /= len;
        z /= len;
        return *this;
    }

    vector_3& vector_3::trunc()
    {
        x = x > 1.0f ? 1.0f : x;
        y = y > 1.0f ? 1.0f : y;
        z = z > 1.0f ? 1.0f : z;
        return *this;
    }

    vector_3& vector_3::operator=(const vector_3& vec)
    {
        if (this != &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }

        return *this;
    }

    vector_3& vector_3::operator+=(const float& num)
    {
        x += num; y += num; z += num;
        return *this;
    }
    vector_3& vector_3::operator-=(const float& num)
    {
        x -= num; y -= num; z -= num;
        return *this;
    }
    vector_3& vector_3::operator*=(const float& num)
    {
        x *= num; y *= num; z *= num;
        return *this;
    }
    vector_3& vector_3::operator/=(const float& num)
    {
        x /= num; y /= num; z /= num;
        return *this;
    }
    vector_3& vector_3::operator+=(const vector_3& vec)
    {
        x += vec.x; y += vec.y; z += vec.z;
        return *this;
    }
    vector_3& vector_3::operator-=(const vector_3& vec)
    {
        x -= vec.x; y -= vec.y; z -= vec.z;
        return *this;
    }
    vector_3& vector_3::operator*=(const vector_3& vec)
    {
        x *= vec.x; y *= vec.y; z *= vec.z;
        return *this;
    }
    vector_3& vector_3::operator/=(const vector_3& vec)
    {
        x /= vec.x; y /= vec.y; z /= vec.z;
        return *this;
    }

    /**
     * Scalar cross product
     */
    float vector_3::operator&=(const vector_3& vec)
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }
    /**
     * Vector cross product
     */
    vector_3& vector_3::operator^=(const vector_3& vec)
    {
        x = y * vec.z - z * vec.y;
        y = z * vec.x - x * vec.z;
        z = x * vec.y - y * vec.x;
        return *this;
    }

    vector_3::operator vector_4()
    {
        return { x, y, z, 1.0f };
    }

    vector_3 operator+(const vector_3& vec_a, const vector_3& vec_b)
    {
        return { vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z };
    }
    vector_3 operator-(const vector_3& vec_a, const vector_3& vec_b)
    {
        return { vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z };
    }
    vector_3 operator*(const vector_3& vec_a, const vector_3& vec_b)
    {
        return { vec_a.x * vec_b.x, vec_a.y * vec_b.y, vec_a.z * vec_b.z };
    }
    vector_3 operator/(const vector_3& vec_a, const vector_3& vec_b)
    {
        return { vec_a.x / vec_b.x, vec_a.y / vec_b.y, vec_a.z / vec_b.z };
    }
    /**
     * Scalar cross product
     */
    float operator&(const vector_3& vec_a, const vector_3& vec_b)
    {
        return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
    }
    /**
     * Vector cross product
     */
    vector_3 operator^(const vector_3& vec_a, const vector_3& vec_b)
    {
        return { vec_a.y * vec_b.z - vec_a.z * vec_b.y,
                 vec_a.z * vec_b.x - vec_a.x * vec_b.z,
                 vec_a.x * vec_b.y - vec_a.y * vec_b.x };
    }

    bool operator==(const vector_3& vec_a, const vector_3& vec_b)
    {
        if ((vec_a.x - vec_b.x) * (vec_a.x - vec_b.x) > eps)
            return false;

        if ((vec_a.y - vec_b.y) * (vec_a.y - vec_b.y) > eps)
            return false;

        if ((vec_a.z - vec_b.z) * (vec_a.z - vec_b.z) > eps)
            return false;

        return true;
    }
    bool operator!=(const vector_3& vec_a, const vector_3& vec_b)
    {
        return !(vec_a == vec_b);
    }

    vector_3 operator+(const float& num, const vector_3& vec)
    {
        return { num + vec.x, num + vec.y, num + vec.z };
    }
    vector_3 operator-(const float& num, const vector_3& vec)
    {
        return { num - vec.x, num - vec.y, num - vec.z };
    }
    vector_3 operator*(const float& num, const vector_3& vec)
    {
        return { num * vec.x, num * vec.y, num * vec.z };
    }
    vector_3 operator/(const float& num, const vector_3& vec)
    {
        return { num / vec.x, num / vec.y, num / vec.z };
    }
    vector_3 operator+(const vector_3& vec, const float& num)
    {
        return { vec.x + num, vec.y + num, vec.z + num };
    }
    vector_3 operator-(const vector_3& vec, const float& num)
    {
        return { vec.x - num, vec.y - num, vec.z - num };
    }
    vector_3 operator*(const vector_3& vec, const float& num)
    {
        return { vec.x * num, vec.y * num, vec.z * num };
    }
    vector_3 operator/(const vector_3& vec, const float& num)
    {
        return { vec.x / num, vec.y / num, vec.z / num };
    }

    /*float distance(vector_3 vec_a, vector_3 vec_b)
    {
        double vec_a_x = static_cast<double>(vec_a.x);
        double vec_a_y = static_cast<double>(vec_a.y);
        double vec_a_z = static_cast<double>(vec_a.z);
        double vec_b_x = static_cast<double>(vec_b.x);
        double vec_b_y = static_cast<double>(vec_b.y);
        double vec_b_z = static_cast<double>(vec_b.z);
        return sqrt((vec_b_x - vec_a_x) * (vec_b_x - vec_a_x) +
            (vec_b_y - vec_a_y) * (vec_b_y - vec_a_y) +
            (vec_b_z - vec_a_z) * (vec_b_z - vec_a_z));
    }*/
    /*float distance(vector_3 vec_a, vector_4 vec_b)
    {
        return distance(vec_a, static_cast<vector_3>(vec_b));
    }
    float distance(vector_4 vec_a, vector_3 vec_b)
    {
        return distance(static_cast<vector_3>(vec_a), vec_b);
    }*/
    /*float distance(vector_4 vec_a, vector_4 vec_b)
    {
        double vec_a_x = static_cast<double>(vec_a.x);
        double vec_a_y = static_cast<double>(vec_a.y);
        double vec_a_z = static_cast<double>(vec_a.z);
        double vec_a_w = static_cast<double>(vec_a.w);
        double vec_b_x = static_cast<double>(vec_b.x);
        double vec_b_y = static_cast<double>(vec_b.y);
        double vec_b_z = static_cast<double>(vec_b.z);
        double vec_b_w = static_cast<double>(vec_b.w);
        return sqrt((vec_b_x - vec_a_x) * (vec_b_x - vec_a_x) +
            (vec_b_y - vec_a_y) * (vec_b_y - vec_a_y) +
            (vec_b_z - vec_a_z) * (vec_b_z - vec_a_z) +
            (vec_b_w - vec_a_w) * (vec_b_w - vec_a_w));
    }*/

    /*float angle(vector_3 vec_a, vector_3 vec_b)
    {
        double arg = static_cast<double>((vec_a & vec_b) / (vec_a.length() * vec_b.length()));
        return static_cast<float>(acos(arg));
    }*/


    float vector_4::length()
    {
        double _x = static_cast<double>(x);
        double _y = static_cast<double>(y);
        double _z = static_cast<double>(z);
        return static_cast<float>(sqrt(_x * _x + _y * _y + _z * _z));
    }

    vector_4& vector_4::normalize()
    {
        float len = length();
        x /= len;
        y /= len;
        z /= len;
        return *this;
    }

    vector_4& vector_4::trunc()
    {
        x = x > 1.0f ? 1.0f : x;
        y = y > 1.0f ? 1.0f : y;
        z = z > 1.0f ? 1.0f : z;
        return *this;
    }

    vector_4& vector_4::operator=(const vector_4& vec)
    {
        if (this != &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
        }

        return *this;
    }

    vector_4& vector_4::operator+=(const float& num)
    {
        x += num; y += num; z += num;
        return *this;
    }
    vector_4& vector_4::operator-=(const float& num)
    {
        x -= num; y -= num; z -= num;
        return *this;
    }
    vector_4& vector_4::operator*=(const float& num)
    {
        x *= num; y *= num; z *= num;
        return *this;
    }
    vector_4& vector_4::operator/=(const float& num)
    {
        x /= num; y /= num; z /= num;
        return *this;
    }
    vector_4& vector_4::operator+=(const vector_4& vec)
    {
        x += vec.x; y += vec.y; z += vec.z;
        return *this;
    }
    vector_4& vector_4::operator-=(const vector_4& vec)
    {
        x -= vec.x; y -= vec.y; z -= vec.z;
        return *this;
    }
    vector_4& vector_4::operator*=(const vector_4& vec)
    {
        x *= vec.x; y *= vec.y; z *= vec.z;
        return *this;
    }
    vector_4& vector_4::operator/=(const vector_4& vec)
    {
        x /= vec.x; y /= vec.y; z /= vec.z;
        return *this;
    }

    vector_4::operator vector_3()
    {
        return { x, y, z };
    }

    vector_4 operator+(const vector_4& vec_a, const vector_4& vec_b)
    {
        return { vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z, vec_a.w + vec_b.w };
    }
    vector_4 operator-(const vector_4& vec_a, const vector_4& vec_b)
    {
        return { vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z, vec_a.w - vec_b.w };
    }
    vector_4 operator*(const vector_4& vec_a, const vector_4& vec_b)
    {
        return { vec_a.x * vec_b.x, vec_a.y * vec_b.y, vec_a.z * vec_b.z, vec_a.w * vec_b.w };
    }
    vector_4 operator/(const vector_4& vec_a, const vector_4& vec_b)
    {
        return { vec_a.x / vec_b.x, vec_a.y / vec_b.y, vec_a.z / vec_b.z, vec_a.w / vec_b.w };
    }

    bool operator==(const vector_4& vec_a, const vector_4& vec_b)
    {
        if ((vec_a.x - vec_b.x) * (vec_a.x - vec_b.x) > eps)
            return false;

        if ((vec_a.y - vec_b.y) * (vec_a.y - vec_b.y) > eps)
            return false;

        if ((vec_a.z - vec_b.z) * (vec_a.z - vec_b.z) > eps)
            return false;

        return true;
    }
    bool operator!=(const vector_4& vec_a, const vector_4& vec_b)
    {
        return !(vec_a == vec_b);
    }

    vector_4 operator+(const float& num, const vector_4& vec)
    {
        return { num + vec.x, num + vec.y, num + vec.z, 1.0f };
    }
    vector_4 operator-(const float& num, const vector_4& vec)
    {
        return { num - vec.x, num - vec.y, num - vec.z, 1.0f };
    }
    vector_4 operator*(const float& num, const vector_4& vec)
    {
        return { num * vec.x, num * vec.y, num * vec.z, 1.0f };
    }
    vector_4 operator/(const float& num, const vector_4& vec)
    {
        return { num / vec.x, num / vec.y, num / vec.z, 1.0f };
    }
    vector_4 operator+(const vector_4& vec, const float& num)
    {
        return { vec.x + num, vec.y + num, vec.z + num, 1.0f };
    }
    vector_4 operator-(const vector_4& vec, const float& num)
    {
        return { vec.x - num, vec.y - num, vec.z - num, 1.0f };
    }
    vector_4 operator*(const vector_4& vec, const float& num)
    {
        return { vec.x * num, vec.y * num, vec.z * num, 1.0f };
    }
    vector_4 operator/(const vector_4& vec, const float& num)
    {
        return { vec.x / num, vec.y / num, vec.z / num, 1.0f };
    }
}