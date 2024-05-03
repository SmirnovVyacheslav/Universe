// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "impl_model.h"

#include <iostream>
#include <filesystem>
#include <fstream>

#include "engine/render/mesh/api_mesh.h"
#include "engine/render/mesh/obj_mesh.h"
#include "engine/render/settings/api_settings.h"
#include "engine/render/shader/api_shader.h"
#include "engine/render/shader/obj_shader.h"

#include "engine/var/std.h"
#include "engine/var/string.h"


namespace engine::render::model
{
    mesh::obj& get_mesh(string model_name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.model.u8_str() + model_name.u8_str() + u8".model");

        string str;
        while ((ifstream >> str) && (str != string(u8"mesh")));
        if (str != string(u8"mesh")) {
            throw std::invalid_argument("Incorrect file format");
        }
        ifstream >> str;
        ifstream.close();

        return mesh::add(str);
    }

    /*shader::obj& get_shader(string model_name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.model.u8_str() + model_name.u8_str() + u8".model");

        string str;
        while ((ifstream >> str) && (str != string(u8"shader")));
        if (str != string(u8"shader")) {
            throw std::invalid_argument("Incorrect file format");
        }
        ifstream >> str;
        ifstream.close();

        return shader::add(str);
    }*/


    impl::impl(string name) :
        mesh_obj(get_mesh(name))
    {}

    void impl::set()
    {
        mesh_obj.set();
    }

    int32 impl::size()
    {
        return mesh_obj.size();
    }

    impl::~impl()
    {}
}
