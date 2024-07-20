// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_vector.h"


#ifndef ENGINE_VECTOR
#define ENGINE_VECTOR

namespace engine
{
    template <int32 size>
    struct vector;
    template <int32 size>
    const fp32 length(const vector<size>& vec);
    template <int32 size>
    const vector<size> normalize(const vector<size>& vec);
    template <int32 size>
    const vector<size> operator+(const vector<size>& vec_a, const vector<size>& vec_b);
    template <int32 size>
    const vector<size> operator-(const vector<size>& vec_a, const vector<size>& vec_b);
    template <int32 size>
    const vector<size> operator+(const vector<size>& vec, const fp32& num);
    template <int32 size>
    const vector<size> operator-(const vector<size>& vec, const fp32& num);
    template <int32 size>
    const vector<size> operator*(const vector<size>& vec, const fp32& num);
    template <int32 size>
    const vector<size> operator/(const vector<size>& vec, const fp32& num);
    template <int32 size>
    const vector<size> operator+(const fp32& num, const vector<size>& vec);
    template <int32 size>
    const vector<size> operator-(const fp32& num, const vector<size>& vec);
    template <int32 size>
    const vector<size> operator*(const fp32& num, const vector<size>& vec);
    template <int32 size>
    const vector<size> operator/(const fp32& num, const vector<size>& vec);
    template <int32 size>
    bool operator==(const vector<size>& vec_a, const vector<size>& vec_b);
    template <int32 size>
    bool operator!=(const vector<size>& vec_a, const vector<size>& vec_b);
    // Scalar product
    template <int32 size>
    const fp32 operator*(const vector<size>& vec_a, const vector<size>& vec_b);
    template <int32 size>
    std::istream& operator>>(std::istream& in_stream, vector<size>& vec);
    template <int32 size>
    std::ostream& operator<<(std::ostream& out_stream, const vector<size>& vec);


    template <int32 size>
    struct vector
    {
        fp32 data[size];

        vector();
        vector(vector&& src) = default;
        vector(const vector& src) = default;

        vector& operator=(vector&& src) = default;
        vector& operator=(const vector& src) = default;
        fp32& operator[](const int32 index);
        const fp32& operator[](const int32 index) const;

        ~vector() = default;

        friend const vector<size> operator+ <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        friend const vector<size> operator- <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        friend const vector<size> operator+ <size> (const vector<size>& vec, const fp32& num);
        friend const vector<size> operator- <size> (const vector<size>& vec, const fp32& num);
        friend const vector<size> operator* <size> (const vector<size>& vec, const fp32& num);
        friend const vector<size> operator/ <size> (const vector<size>& vec, const fp32& num);
        friend const vector<size> operator+ <size> (const fp32& num, const vector<size>& vec);
        friend const vector<size> operator- <size> (const fp32& num, const vector<size>& vec);
        friend const vector<size> operator* <size> (const fp32& num, const vector<size>& vec);
        friend const vector<size> operator/ <size> (const fp32& num, const vector<size>& vec);
        friend bool operator== <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        friend bool operator!= <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        // Scalar product
        friend const fp32 operator* <size> (const vector<size>& vec_a, const vector<size>& vec_b);
        friend std::istream& operator>> <size> (std::istream& in_stream, vector<size>& vec);
        friend std::ostream& operator<< <size> (std::ostream& out_stream, const vector<size>& vec);
    };


    template <int32 size>
    vector<size>::vector()
    {
        if (size <= 0)
        {
            throw error("Vector size should be positive");
        }
        for (int32 i = 0; i < size; ++i)
        {
            data[i] = 0.0f;
        }
    }

    template <int32 size>
    fp32& vector<size>::operator[](const int32 index)
    {
        return data[(size + index % size) % size];
    }

    template <int32 size>
    const fp32& vector<size>::operator[](const int32 index) const
    {
        return data[(size + index % size) % size];
    }


    template <int32 size>
    const fp32 length(const vector<size>& vec)
    {
        return sqrtf(vec * vec);
    }

    template <int32 size>
    const vector<size> normalize(const vector<size>& vec)
    {
        fp32 vec_length = length(vec);
        if (vec_length < eps)
        {
            throw error("Vector length is zero - division by zero");
        }
        return vec / vec_length;
    }

    template <int32 size>
    const vector<size> operator+(const vector<size>& vec_a, const vector<size>& vec_b) {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = vec_a[i] + vec_b[i];
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator-(const vector<size>& vec_a, const vector<size>& vec_b)
    {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = vec_a[i] - vec_b[i];
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator+(const vector<size>& vec, const fp32& num)
    {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = vec[i] + num;
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator-(const vector<size>& vec, const fp32& num)
    {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = vec[i] - num;
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator*(const vector<size>& vec, const fp32& num)
    {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = vec[i] * num;
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator/(const vector<size>& vec, const fp32& num)
    {
        if (num < eps)
        {
            throw error("Division by zero");
        }
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = vec[i] / num;
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator+(const fp32& num, const vector<size>& vec)
    {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = num + vec[i];
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator-(const fp32& num, const vector<size>& vec)
    {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = num - vec[i];
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator*(const fp32& num, const vector<size>& vec)
    {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            vec_res[i] = num * vec[i];
        }
        return vec_res;
    }

    template <int32 size>
    const vector<size> operator/(const fp32& num, const vector<size>& vec)
    {
        vector<size> vec_res;
        for (int32 i = 0; i < size; ++i)
        {
            if (vec[i] < eps)
            {
                throw error("Division by zero");
            }
            vec_res[i] = num / vec[i];
        }
        return vec_res;
    }

    template <int32 size>
    bool operator==(const vector<size>& vec_a, const vector<size>& vec_b)
    {
        for (int32 i = 0; i < size; ++i)
        {
            if ((vec_a[i] - vec_b[i]) * (vec_a[i] - vec_b[i]) > eps)
            {
                return false;
            }
        }
        return true;
    }

    template <int32 size>
    bool operator!=(const vector<size>& vec_a, const vector<size>& vec_b)
    {
        return !(vec_a == vec_b);
    }

    // Scalar product
    template <int32 size>
    const fp32 operator*(const vector<size>& vec_a, const vector<size>& vec_b)
    {
        fp32 result = 0.0f;
        for (int32 i = 0; i < size; ++i)
        {
            result += vec_a[i] * vec_b[i];
        }
        return result;
    }

    template <int32 size>
    std::istream& operator>>(std::istream& in_stream, vector<size>& vec)
    {
        for (int32 i = 0; i < size; ++i)
        {
            in_stream >> vec[i];
        }
        return in_stream;
    }

    template <int32 size>
    std::ostream& operator<<(std::ostream& out_stream, const vector<size>& vec)
    {
        for (int32 i = 0; i < size; ++i)
        {
            out_stream << vec[i] << " ";
        }
        out_stream << std::endl;
        return out_stream;
    }
}

#endif
