// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include <filesystem>
#include "resource.h"
#include "src/core/config.h"


namespace engine {
    resource resource::inst = resource();


    void resource::load() {
        //
    }
    void resource::load_mesh() {
        for (const auto& mesh_file : std::filesystem::directory_iterator(config::resource()->mesh_path.s_str())) {
            //
        }
    }
}
