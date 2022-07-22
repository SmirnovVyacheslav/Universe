// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <vector>
#include "src/core/data_type/vector_3.h"
#include "src/core/data_type/vector_4.h"


namespace engine {
    class vertex {
        public:
            vertex() = default;
            ~vertex() = default;
            vertex(vector_3 pos, vector_4 color);
        private:
            vector_3 pos;
            vector_4 color;
    };
    class mesh {
        public:
            mesh();
            ~mesh() = default;
            
            vertex& get_vertex();
            unsigned short& get_indice();
            int get_size();
        private:
            int size;
            std::vector<vertex> vertices;
            std::vector<unsigned short> indices;
    };
}
