// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "vector3.h"
#include "vector4.h"


namespace engine
{
    class vertex
    {
    public:
        vertex() = default;
        vertex(const vector3& pos, const vector4& color);
        vertex(vertex&& src) = default;
        vertex(const vertex& src) = default;

        vertex& operator=(vertex&& src) = default;
        vertex& operator=(const vertex& src) = default;

        ~vertex() = default;
    private:
        vector3 pos;
        vector4 color;
    };
}
