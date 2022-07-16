// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "mesh.h"
#include "src/core/3d_math.h"
#include "src/core/data_types/vector_3.h"


namespace engine
{
    //vector_3_tmp tmp_vec(1.0f, 2.0f, 3.0f);
    //vector_3_tmp tmp_vec_2(1.0f, 3.0f, 3.0f);
    //// vector_3_tmp tmp_vec_3 = tmp_vec + tmp_vec_2;

    vector<static_cast<uint_32>(3)> tmp_vec;
    vector<static_cast<uint_32>(3)> tmp_vec_2;
    vector<static_cast<uint_32>(3)> tmp_vec_3 = tmp_vec + tmp_vec_2;
    vertex::vertex(vector_3 pos, vector_4 color) :
        pos(pos), color(color)
    {
        //
    }


    mesh::mesh()
    {
        vertices =
        {
            { vector_3(-1.0f, 1.0f, -1.0f), vector_4(0.0f, 0.0f, 1.0f, 1.0f) },
            { vector_3(1.0f, 1.0f, -1.0f), vector_4(0.0f, 1.0f, 0.0f, 1.0f) },
            { vector_3(1.0f, 1.0f, 1.0f), vector_4(0.0f, 1.0f, 1.0f, 1.0f) },
            { vector_3(-1.0f, 1.0f, 1.0f), vector_4(1.0f, 0.0f, 0.0f, 1.0f) },
            { vector_3(-1.0f, -1.0f, -1.0f), vector_4(1.0f, 0.0f, 1.0f, 1.0f) },
            { vector_3(1.0f, -1.0f, -1.0f), vector_4(1.0f, 1.0f, 0.0f, 1.0f) },
            { vector_3(1.0f, -1.0f, 1.0f), vector_4(1.0f, 1.0f, 1.0f, 1.0f) },
            { vector_3(-1.0f, -1.0f, 1.0f), vector_4(0.0f, 0.0f, 0.0f, 1.0f) },
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
