// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "std.h"


namespace engine {
    template <uint_32 size>
    struct vector;
    union vector_3;
    union vector_4;


    template <uint_32 size>
    using vector = struct vector;
    using vector_3 = union vector_3;
    using vector_4 = union vector_4;


    template <uint_32 size>
    struct vector {
        real_32[size] data;
    };
    union vector_3 {
        vector<static_cast<uint_32>(3)> data;
        struct {
            real_32 x;
            real_32 y;
            real_32 z;
        };
    };
    union vector_4 {
        vector<static_cast<uint_32>(4)> data;
        struct {
            real_32 x;
            real_32 y;
            real_32 z;
            real_32 w;
        };
    };
}
