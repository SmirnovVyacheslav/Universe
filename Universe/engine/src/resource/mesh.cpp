// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "mesh.h"


namespace engine
{
    vertex::vertex(vector_3_tmp pos, vector_4_tmp color) :
        pos(pos), color(color)
    {
        //
    }


    mesh::mesh()
    {
        vertices =
        {
            { vector_3_tmp(-1.0f, 1.0f, -1.0f), vector_4_tmp(0.0f, 0.0f, 1.0f, 1.0f) },
            { vector_3_tmp(1.0f, 1.0f, -1.0f), vector_4_tmp(0.0f, 1.0f, 0.0f, 1.0f) },
            { vector_3_tmp(1.0f, 1.0f, 1.0f), vector_4_tmp(0.0f, 1.0f, 1.0f, 1.0f) },
            { vector_3_tmp(-1.0f, 1.0f, 1.0f), vector_4_tmp(1.0f, 0.0f, 0.0f, 1.0f) },
            { vector_3_tmp(-1.0f, -1.0f, -1.0f), vector_4_tmp(1.0f, 0.0f, 1.0f, 1.0f) },
            { vector_3_tmp(1.0f, -1.0f, -1.0f), vector_4_tmp(1.0f, 1.0f, 0.0f, 1.0f) },
            { vector_3_tmp(1.0f, -1.0f, 1.0f), vector_4_tmp(1.0f, 1.0f, 1.0f, 1.0f) },
            { vector_3_tmp(-1.0f, -1.0f, 1.0f), vector_4_tmp(0.0f, 0.0f, 0.0f, 1.0f) },
        };

        indices =  {
            3,1,0,
            2,1,3,

            0,5,4,
            1,5,0,

            3,4,7,
            0,4,3,

            1,6,5,
            2,6,1,

            2,7,6,
            3,7,2,

            6,4,5,
            7,4,6,
        };

        size = 36;
    }

    vertex& mesh::get_vertex()
    {
        return vertices[0];
    }


    unsigned short& mesh::get_indice()
    {
        return indices[0];
    }


    int mesh::get_size()
    {
        return size;
    }
}
