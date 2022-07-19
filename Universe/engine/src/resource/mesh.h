// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef MESH_H
#define MESH_H

//#include "src/core/3d_math.h"
#include "src/core/data_type/vector_3.h"
#include "src/core/data_type/vector_4.h"
#include <vector>


namespace engine
{
    class vertex
    {
    public:
        vertex() = default;
        ~vertex() = default;

        vertex(vector_3_tmp pos, vector_4_tmp color);

    private:
        vector_3_tmp pos;
        vector_4_tmp color;
    };


    class mesh
    {
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
#endif
