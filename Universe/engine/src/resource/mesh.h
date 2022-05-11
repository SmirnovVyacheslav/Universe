// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef MESH_H
#define MESH_H

#include "src/core/math.h"
#include "src/platform/container.h"


namespace engine
{
    class vertex
    {
    public:
        vertex() = default;
        ~vertex() = default;
    };


    class mesh
    {
    public:
        mesh() = default;
        ~mesh() = default;

    private:
        int size;
        platform::vector<vertex> vertices;
        platform::vector<unsigned long int> indices;
    };
}
#endif
