// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "mesh.h"
#include "src/core/3d_math.h"
#include "src/core/data_type/vector_3.h"


namespace engine
{
    vector_3_tmp tmp_vec_20(1.0f, 2.0f, 3.0f);
    vector_3_tmp tmp_vec_21(1.0f, 3.0f, 3.0f);
    vector_3_tmp tmp_vec_22 = tmp_vec_20 + tmp_vec_21;
    vector_3_tmp tmp_vec_23 = tmp_vec_20 - tmp_vec_21;
    real_32 tmp_vec_24 = tmp_vec_20 * tmp_vec_21;
    vector_3_tmp tmp_vec_25 = tmp_vec_20 ^ tmp_vec_21;

    vector<static_cast<uint_32>(3)> tmp_vec;
    vector<static_cast<uint_32>(3)> tmp_vec_2;
    vector<static_cast<uint_32>(3)> tmp_vec_3 = tmp_vec + tmp_vec_2;
    vector<static_cast<uint_32>(3)> tmp_vec_4 = tmp_vec - tmp_vec_2;
    vector<static_cast<uint_32>(3)> tmp_vec_5 = tmp_vec + 1.0f;
    vector<static_cast<uint_32>(3)> tmp_vec_6 = tmp_vec + 1.0f;
    vector<static_cast<uint_32>(3)> tmp_vec_7 = tmp_vec * 1.0f;
    vector<static_cast<uint_32>(3)> tmp_vec_8 = tmp_vec / 1.0f;
    vector<static_cast<uint_32>(3)> tmp_vec_9 = 1.0f + tmp_vec_2;
    vector<static_cast<uint_32>(3)> tmp_vec_10 = 1.0f + tmp_vec_2;
    vector<static_cast<uint_32>(3)> tmp_vec_11 = 1.0f * tmp_vec_2;
    vector<static_cast<uint_32>(3)> tmp_vec_12 = 1.0f / tmp_vec_2;
    bool tmp_vec_13 = tmp_vec == tmp_vec_2;
    bool tmp_vec_14 = tmp_vec != tmp_vec_2;
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
