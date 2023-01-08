// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <iostream>

#include "array.h"
#include "std.h"
#include "vertex.h"
#include "string.h"


namespace engine {
    class mesh {
    public:
        mesh() = default;
        mesh(mesh&& src) = default;
        mesh(const mesh& src) = default;

        static string name();

        uint_32 size();
        vertex_tmp& vertices();
        uint_16& indices();

        mesh& operator=(mesh&& src) = default;
        mesh& operator=(const mesh& src) = default;

        ~mesh() = default;
    private:
        array<vertex_tmp> vertex_array;
        array<uint_16> index_array;

        friend std::istream& operator>>(std::istream& in_stream, mesh& mesh_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const mesh& mesh_obj);
    };
}
