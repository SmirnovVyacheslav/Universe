// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/vector.h"


namespace engine {
    union vector_3_tmp {
        vector<static_cast<uint_32>(3)> data;
        struct {
            real_32 x;
            real_32 y;
            real_32 z;
        };

        vector_3_tmp() = default;
        vector_3_tmp(real_32 x, real_32 y, real_32 z);
        ~vector_3_tmp() = default;
        vector_3_tmp(vector_3_tmp&& src) = default;
        vector_3_tmp(const vector_3_tmp& src) = default;

        vector_3_tmp& operator=(vector_3_tmp&& src) = default;
        vector_3_tmp& operator=(const vector_3_tmp& src) = default;
        //real_32& operator[](const int_32 index);
    };
}
