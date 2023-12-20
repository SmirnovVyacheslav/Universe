// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/type/vector3.h"
#include "src/core/type/vector4.h"
#include "src/core/def/class_format.h"

namespace engine
{
    class vertex
    {
        ____________________public____________________
        vertex() = default;
        vertex(const vector3& pos, const vector4& color);
        vertex(vertex&& src) = default;
        vertex(const vertex& src) = default;

        vertex& operator=(vertex&& src) = default;
        vertex& operator=(const vertex& src) = default;

        ~vertex() = default;
        ____________________private___________________
        vector3 pos;
        vector4 color;
    };
}
