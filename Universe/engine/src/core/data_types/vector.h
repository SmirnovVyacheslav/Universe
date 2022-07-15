// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/math/const.h"
#include "src/core/math/vector.h"


namespace engine {
    template <uint_32 size>
    struct vector {
        real_32 data[size];

        vector();
        ~vector() = default;
        vector(vector&& src) = default;
        vector(const vector& src) = default;

        vector& operator=(vector&& src) = default;
        vector& operator=(const vector& src) = default;
        real_32& operator[](const int_32 index);
    };


    template <uint_32 size>
    vector<size>::vector() {
        for (uint_32 i = 0; i < size; ++i) {
            data[i] = 0.0f;
        }
    }
    template <uint_32 size>
    real_32& vector<size>::operator[](const int_32 index) {
        int_32 size_int_32 = static_cast<int_32>(size);
        return data[(size_int_32 + index % size_int_32) % size_int_32];
    }
}
