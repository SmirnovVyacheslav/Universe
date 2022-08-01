// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <iostream>
#include "array.h"
#include "vertex.h"


namespace engine {
    class mesh {
        friend std::istream& operator>>(std::istream& in_stream, mesh& mesh_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const mesh& mesh_obj);
        public:
            mesh() = default;
            ~mesh() = default;
            mesh(mesh&& src) = default;
            mesh(const mesh& src) = default;

            mesh& operator=(mesh&& src) = default;
            mesh& operator=(const mesh& src) = default;

            uint_32 size();
            vertex& vertices();
            uint_16& indices();
        private:
            array<vertex> vertex_array;
            array<uint_16> index_array;
    };
}
