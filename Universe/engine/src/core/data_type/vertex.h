// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "vector_3.h"
#include "vector_4.h"


namespace engine {
    class vertex_tmp {
    public:
        vertex_tmp() = default;
        vertex_tmp(const vector_3& pos, const vector_4& color);
        vertex_tmp(vertex_tmp&& src) = default;
        vertex_tmp(const vertex_tmp& src) = default;

        vertex_tmp& operator=(vertex_tmp&& src) = default;
        vertex_tmp& operator=(const vertex_tmp& src) = default;

        ~vertex_tmp() = default;
    private:
        vector_3 pos;
        vector_4 color;
    };
}
