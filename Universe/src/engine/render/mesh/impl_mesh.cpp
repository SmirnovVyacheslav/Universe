// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "impl_mesh.h"

#include "engine/render/index/api_index.h"
#include "engine/render/settings/api_settings.h"
#include "engine/render/vertices/api_vertices.h"

#include <iostream>
#include <filesystem>
#include <fstream>


namespace engine::render::mesh
{
    static index::obj& get_index(string mesh_name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.mesh.u8_str() + mesh_name.u8_str() + u8".mesh");

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

        return index::add(index_arr);
    }

    static vertices::obj& get_vertices(string mesh_name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.mesh.u8_str() + mesh_name.u8_str() + u8".mesh");

        string str;
        while ((ifstream >> str) && (str != string(u8"vertex")));
        if (str != string(u8"vertex")) {
            throw std::invalid_argument("Incorrect file format");
        }

        vector3 vertex_val;
        uint32 vertex_num = 0;
        array<vertex> vertex_arr;

        ifstream >> vertex_num;
        for (uint32 i = 0; i < vertex_num; ++i) {
            ifstream >> vertex_val;
            vertex_arr.append(vertex(vertex_val, vector4(0.0f, 0.0f, 1.0f, 1.0f)));
        }
        ifstream.close();

        return vertices::add(vertex_arr);
    }


    impl::impl(string mesh_name) :
        index_obj(get_index(mesh_name)),
        vertices_obj(get_vertices(mesh_name))
    {}

    void impl::set()
    {
        index_obj.set();
        vertices_obj.set();
    }

    int32 impl::size()
    {
        return index_obj.size();
    }

    impl::~impl()
    {}
}
