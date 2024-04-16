// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "obj_mesh.h"

#include "engine/var/array.h"
#include "engine/var/std.h"
#include "engine/var/vector3.h"
#include "engine/var/vector4.h"
#include "engine/var/vertex.h"

#include <iostream>
#include <filesystem>
#include <fstream>


namespace engine::render::mesh
{
    obj::obj(string file)
    {
        array<uint16> index_arr;
        array<engine::vertex> vertex_arr;

        std::ifstream input_stream;
        input_stream.open(file.u8_str());

        string str;
        input_stream >> str;
        if (str != string(u8"vertices")) {
            throw std::invalid_argument("Incorrect file format");
        }
        std::cout << str;

        uint32 vertex_num = 0;
        input_stream >> vertex_num;
        vector3 vertex;
        
        for (uint32 i = 0; i < vertex_num; ++i) {
            input_stream >> vertex;
            vertex_arr.append(engine::vertex(vertex, vector4(0.0f, 0.0f, 1.0f, 1.0f)));
        }

        input_stream >> str;
        if (str != string(u8"indices")) {
            throw std::invalid_argument("Incorrect file format");
        }

        uint32 indices_num = 0;
        input_stream >> indices_num;
        uint16 index;
        
        for (uint32 i = 0; i < indices_num; ++i) {
            input_stream >> index;
            index_arr.append(index);
        }

        input_stream.close();
    }

    void obj::set()
    {
        //
    }

    obj::~obj()
    {
        // delete index_obj;
        // delete vertex_obj;
    }

}
