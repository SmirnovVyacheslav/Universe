// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef MESH_H
#define MESH_H

#include "src/core/math.h"
#include <vector>


namespace engine
{
    class vertex
    {
    public:
        vertex() = default;
        ~vertex() = default;

        vertex(vector_3 pos, vector_4 color);

    private:
        vector_3 pos;
        vector_4 color;
    };


    class mesh
    {
    public:
        mesh();
        ~mesh() = default;

    private:
        int size;
        std::vector<vertex> vertices;
        std::vector<unsigned long int> indices;
    };
}
#endif
