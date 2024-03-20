// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_index.h"

#include "directx/impl_index.h"


namespace engine::render::index
{
    obj* inst = nullptr;


    void init()
    {
        uint16* index_data = new uint16[36];
        index_data[0] = 3;
        index_data[1] = 1;
        index_data[2] = 0;
        index_data[3] = 2;
        index_data[4] = 1;
        index_data[5] = 3;
        index_data[6] = 0;
        index_data[7] = 5;
        index_data[8] = 4;
        index_data[9] = 1;
        index_data[10] = 5;
        index_data[11] = 0;
        index_data[12] = 3;
        index_data[13] = 4;
        index_data[14] = 7;
        index_data[15] = 0;
        index_data[16] = 4;
        index_data[17] = 3;
        index_data[18] = 1;
        index_data[19] = 6;
        index_data[20] = 5;
        index_data[21] = 2;
        index_data[22] = 6;
        index_data[23] = 1;
        index_data[24] = 2;
        index_data[25] = 7;
        index_data[26] = 6;
        index_data[27] = 3;
        index_data[28] = 7;
        index_data[29] = 2;
        index_data[30] = 6;
        index_data[31] = 4;
        index_data[32] = 5;
        index_data[33] = 7;
        index_data[34] = 4;
        index_data[35] = 6;

        inst = new directx::impl(index_data);
    }

    obj& get()
    {
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
