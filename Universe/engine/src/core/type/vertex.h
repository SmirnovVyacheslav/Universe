// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "vector_3.h"
#include "vector_4.h"


namespace engine {
    class vertex {
    public:
        vertex() = default;
        vertex(const vector_3& pos, const vector_4& color);
        vertex(vertex&& src) = default;
        vertex(const vertex& src) = default;

        vertex& operator=(vertex&& src) = default;
        vertex& operator=(const vertex& src) = default;

        ~vertex() = default;
    private:
        vector_3 pos;
        vector_4 color;
    };
}
