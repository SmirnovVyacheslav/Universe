// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/type/vector_3.h"
#include "src/core/type/vector_4.h"
#include "src/core/def/class_format.h"

namespace engine
{
    class vertex
    {
        ____________________public____________________
        vertex() = default;
        vertex(const vector_3& pos, const vector_4& color);
        vertex(vertex&& src) = default;
        vertex(const vertex& src) = default;

        vertex& operator=(vertex&& src) = default;
        vertex& operator=(const vertex& src) = default;

        ~vertex() = default;
        ____________________private___________________
        vector_3 pos;
        vector_4 color;
    };
}
