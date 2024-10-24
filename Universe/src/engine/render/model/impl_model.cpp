// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_impl_model.h"


namespace engine::render::model
{
    static mesh::obj& get_mesh(string model_name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.game.model.u8_str() + model_name.u8_str() + u8".model");

        string str;
        while ((ifstream >> str) && (str != string(u8"mesh")));
        if (str != string(u8"mesh")) {
            throw std::invalid_argument("Incorrect file format");
        }
        ifstream >> str;
        ifstream.close();

        return mesh::add(str);
    }

    static shader::obj& get_shader(string model_name)
    {
        std::ifstream ifstream;
        ifstream.open(settings::get().dir.game.model.u8_str() + model_name.u8_str() + u8".model");

        string str;
        while ((ifstream >> str) && (str != string(u8"shader")));
        if (str != string(u8"shader")) {
            throw std::invalid_argument("Incorrect file format");
        }
        ifstream >> str;
        ifstream.close();

        return shader::add(settings::get().dir.game.shader.u8_str() + str.u8_str() + u8".fx");
    }


    impl::impl(string name) :
        mesh_obj(get_mesh(name)),
        shader_obj(get_shader(name))
    {}

    void impl::set()
    {
        mesh_obj.set();
        shader_obj.set();
    }

    int32 impl::size()
    {
        return mesh_obj.size();
    }

    impl::~impl()
    {}
}
