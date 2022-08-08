// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "std.h"
#include "array.h"
#include "vertex.h"
#include <iostream>


namespace engine {
    class mesh_tmp {
        friend std::istream& operator>>(std::istream& in_stream, mesh_tmp& mesh_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const mesh_tmp& mesh_obj);
        public:
            mesh_tmp() = default;
            mesh_tmp(mesh_tmp&& src) = default;
            mesh_tmp(const mesh_tmp& src) = default;

            uint_32 size();
            vertex_tmp& vertices();
            uint_16& indices();

            mesh_tmp& operator=(mesh_tmp&& src) = default;
            mesh_tmp& operator=(const mesh_tmp& src) = default;

            ~mesh_tmp() = default;
        private:
            array<vertex_tmp> vertex_array;
            array<uint_16> index_array;
    };
}
