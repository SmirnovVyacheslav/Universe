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
    }
    void resource::load_mesh() {
        mesh_tmp mesh_obj;
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
}
