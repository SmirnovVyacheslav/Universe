// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include <iostream>
#include <fstream>
#include <filesystem>
#include "resource.h"
#include "src/core/config.h"


namespace engine {
    resource resource::inst = resource();


    void resource::load() {
        resource::inst.load_mesh();
        resource::inst.load_shader();
    }
    slave_ptr<mesh_tmp>& resource::mesh_prt(const string name) {
        return resource::inst.mesh_map[name].create_slave_ptr();
    }
    slave_ptr<shader>& resource::shader_prt(const string name) {
        return resource::inst.shader_map[name].create_slave_ptr();
    }
    slave_ptr<model>& resource::model_prt(const string name) {
        return resource::inst.model_map[name].create_slave_ptr();
    }
    void resource::load_mesh() {
        std::ifstream mesh_file;
        for (const auto& mesh_file_path : std::filesystem::directory_iterator(config::resource()->mesh_path.s_str())) {
            string file_name = mesh_file_path.path().filename().u8string();
            mesh_map.add(file_name, lead_ptr<mesh_tmp>());
            mesh_map[file_name].initialize();

            mesh_file.open(mesh_file_path);
            mesh_file >> *mesh_map[file_name];
            mesh_file.close();
        }
    }
    void resource::load_shader() {
        std::ifstream shader_file;
        for (const auto& shader_file_path : std::filesystem::directory_iterator(config::resource()->shader_path.s_str())) {
            string file_name = shader_file_path.path().filename().u8string();
            shader_map.add(file_name, lead_ptr<shader>());
            shader_map[file_name].initialize();

            shader_file.open(shader_file_path);
            shader_file >> *shader_map[file_name];
            shader_file.close();
        }
    }
}
