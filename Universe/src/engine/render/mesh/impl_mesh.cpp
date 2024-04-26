// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "impl_mesh.h"

#include "engine/var/vector3.h"
#include "engine/var/vector4.h"

#include <iostream>
#include <filesystem>
#include <fstream>


namespace engine::render::mesh
{
    impl::impl(string file) :
        index_obj(index::add(load_index_data(file))),
        vertex_obj(vertex::add(load_vertex_data(file)))
    {}

    void impl::set()
    {
        index_obj.set();
        vertex_obj.set();
    }

    impl::~impl()
    {}

    array<uint16> impl::load_index_data(string file)
    {
        std::ifstream ifstream;
        ifstream.open(file.u8_str());

        string str;
        while ((ifstream >> str) && (str != string(u8"index")));
        if (str != string(u8"index")) {
            throw std::invalid_argument("Incorrect file format");
        }

        uint16 index_val;
        uint32 index_num = 0;
        array<uint16> index_arr;

        ifstream >> index_num;
        for (uint32 i = 0; i < index_num; ++i) {
            ifstream >> index_val;
            index_arr.append(index_val);
        }

        ifstream.close();
        return index_arr;
    }

    array<engine::vertex> impl::load_vertex_data(string file)
    {
        std::ifstream ifstream;
        ifstream.open(file.u8_str());

        string str;
        while ((ifstream >> str) && (str != string(u8"vertex")));
        if (str != string(u8"vertex")) {
            throw std::invalid_argument("Incorrect file format");
        }

        vector3 vertex_val;
        uint32 vertex_num = 0;
        array<engine::vertex> vertex_arr;

        ifstream >> vertex_num;
        for (uint32 i = 0; i < vertex_num; ++i) {
            ifstream >> vertex_val;
            vertex_arr.append(engine::vertex(vertex_val, vector4(0.0f, 0.0f, 1.0f, 1.0f)));
        }

        ifstream.close();
        return vertex_arr;
    }
}
