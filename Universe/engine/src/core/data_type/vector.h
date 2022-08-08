// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "std.h"
#include "src/core/math/const.h"
#include <math.h>
#include <iostream>
#include <stdexcept>


namespace engine {
    template <int_32 size>
    struct vector;
    template <int_32 size>
    const real_32 length(const vector<size>& vec);
    template <int_32 size>
    const vector<size> normalize(const vector<size>& vec);
    template <int_32 size>
    const vector<size> operator+(const vector<size>& vec_a, const vector<size>& vec_b);
    template <int_32 size>
    const vector<size> operator-(const vector<size>& vec_a, const vector<size>& vec_b);
    template <int_32 size>
    const vector<size> operator+(const vector<size>& vec, const real_32& num);
    template <int_32 size>
    const vector<size> operator-(const vector<size>& vec, const real_32& num);
    template <int_32 size>
    const vector<size> operator*(const vector<size>& vec, const real_32& num);
    template <int_32 size>
    const vector<size> operator/(const vector<size>& vec, const real_32& num);
    template <int_32 size>
    const vector<size> operator+(const real_32& num, const vector<size>& vec);
    template <int_32 size>
    const vector<size> operator-(const real_32& num, const vector<size>& vec);
    template <int_32 size>
    const vector<size> operator*(const real_32& num, const vector<size>& vec);
    template <int_32 size>
    const vector<size> operator/(const real_32& num, const vector<size>& vec);
    template <int_32 size>
    bool operator==(const vector<size>& vec_a, const vector<size>& vec_b);
    template <int_32 size>
    bool operator!=(const vector<size>& vec_a, const vector<size>& vec_b);
    // Scalar product
    template <int_32 size>
    const real_32 operator*(const vector<size>& vec_a, const vector<size>& vec_b);
    template <int_32 size>
    std::istream& operator>>(std::istream& in_stream, vector<size>& vec);
    template <int_32 size>
    std::ostream& operator<<(std::ostream& out_stream, const vector<size>& vec);


    template <int_32 size>
    struct vector {
        real_32 data[size];

        vector();
        vector(vector&& src) = default;
        vector(const vector& src) = default;

        vector& operator=(vector&& src) = default;
        vector& operator=(const vector& src) = default;
        real_32& operator[](const int_32 index);
        const real_32& operator[](const int_32 index) const;

        ~vector() = default;

        friend const vector<size> operator+ <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        friend const vector<size> operator- <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        friend const vector<size> operator+ <size> (const vector<size>& vec, const real_32& num);
        friend const vector<size> operator- <size> (const vector<size>& vec, const real_32& num);
        friend const vector<size> operator* <size> (const vector<size>& vec, const real_32& num);
        friend const vector<size> operator/ <size> (const vector<size>& vec, const real_32& num);
        friend const vector<size> operator+ <size> (const real_32& num, const vector<size>& vec);
        friend const vector<size> operator- <size> (const real_32& num, const vector<size>& vec);
        friend const vector<size> operator* <size> (const real_32& num, const vector<size>& vec);
        friend const vector<size> operator/ <size> (const real_32& num, const vector<size>& vec);
        friend bool operator== <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        friend bool operator!= <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        // Scalar product
        friend const real_32 operator* <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        friend std::istream& operator>> <size> (std::istream& in_stream, vector<size>& vec);
        friend std::ostream& operator<< <size> (std::ostream& out_stream, const vector<size>& vec);
    };


    template <int_32 size>
    vector<size>::vector() {
        if (size <= 0) {
            throw std::invalid_argument("Vector size should be positive");
        }
        for (int_32 i = 0; i < size; ++i) {
            data[i] = 0.0f;
        }
    }
    template <int_32 size>
    real_32& vector<size>::operator[](const int_32 index) {
        return data[(size + index % size) % size];
    }
    template <int_32 size>
    const real_32& vector<size>::operator[](const int_32 index) const {
        return data[(size + index % size) % size];
    }


    template <int_32 size>
    const real_32 length(const vector<size>& vec) {
        return sqrtf(vec * vec);
    }
    template <int_32 size>
    const vector<size> normalize(const vector<size>& vec) {
        real_32 vec_length = length(vec);
        if (vec_length < eps) {
            throw std::invalid_argument("Vector length is zero - division by zero");
        }
        return vec / vec_length;
    }
    template <int_32 size>
    const vector<size> operator+(const vector<size>& vec_a, const vector<size>& vec_b) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = vec_a[i] + vec_b[i];
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator-(const vector<size>& vec_a, const vector<size>& vec_b) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = vec_a[i] - vec_b[i];
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator+(const vector<size>& vec, const real_32& num) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = vec[i] + num;
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator-(const vector<size>& vec, const real_32& num) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = vec[i] - num;
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator*(const vector<size>& vec, const real_32& num) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = vec[i] * num;
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator/(const vector<size>& vec, const real_32& num) {
        if (num < eps) {
            throw std::invalid_argument("Division by zero");
        }
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = vec[i] / num;
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator+(const real_32& num, const vector<size>& vec) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = num + vec[i];
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator-(const real_32& num, const vector<size>& vec) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = num - vec[i];
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator*(const real_32& num, const vector<size>& vec) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            vec_res[i] = num * vec[i];
        }
        return vec_res;
    }
    template <int_32 size>
    const vector<size> operator/(const real_32& num, const vector<size>& vec) {
        vector<size> vec_res;
        for (int_32 i = 0; i < size; ++i) {
            if (vec[i] < eps) {
                throw std::invalid_argument("Division by zero");
            }
            vec_res[i] = num / vec[i];
        }
        return vec_res;
    }
    template <int_32 size>
    bool operator==(const vector<size>& vec_a, const vector<size>& vec_b) {
        for (int_32 i = 0; i < size; ++i) {
            if ((vec_a[i] - vec_b[i]) * (vec_a[i] - vec_b[i]) > eps) {
                return false;
            }
        }
        return true;
    }
    template <int_32 size>
    bool operator!=(const vector<size>& vec_a, const vector<size>& vec_b) {
        return !(vec_a == vec_b);
    }
    // Scalar product
    template <int_32 size>
    const real_32 operator*(const vector<size>& vec_a, const vector<size>& vec_b) {
        real_32 result = 0.0f;
        for (int_32 i = 0; i < size; ++i) {
            result += vec_a[i] * vec_b[i];
        }
        return result;
    }
    template <int_32 size>
    std::istream& operator>>(std::istream& in_stream, vector<size>& vec) {
        for (int_32 i = 0; i < size; ++i) {
            in_stream >> vec[i];
        }
        return in_stream;
    }
    template <int_32 size>
    std::ostream& operator<<(std::ostream& out_stream, const vector<size>& vec) {
        for (int_32 i = 0; i < size; ++i) {
            out_stream << vec[i] << " ";
        }
        out_stream << std::endl;
        return out_stream;
    }
}
