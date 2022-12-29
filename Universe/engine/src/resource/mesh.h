// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <vector>

#include "src/core/data_type/vector_3.h"
#include "src/core/data_type/vector_4.h"


namespace engine {
    class vertex {
    public:
        vertex() = default;
        vertex(vector_3 pos, vector_4 color);
        vertex(vertex&& src) = default;
        vertex(const vertex& src) = default;

        vertex& operator=(vertex&& src) = default;
        vertex& operator=(const vertex& src) = default;

        ~vertex() = default;
    private:
        vector_3 pos;
        vector_4 color;
    };
    class mesh {
    public:
        mesh();
        mesh(mesh&& src) = default;
        mesh(const mesh& src) = default;

        mesh& operator=(mesh&& src) = default;
        mesh& operator=(const mesh& src) = default;
        
        vertex& get_vertex();
        unsigned short& get_indice();
        int get_size();

        ~mesh() = default;
    private:
        int size;
        std::vector<vertex> vertices;
        std::vector<unsigned short> indices;
    };
}
