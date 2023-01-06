// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include <iostream>
#include <fstream>
#include <filesystem>

#include "config.h"


namespace engine {
    void config::initialize() {
        config& inst = config::get_inst();
        inst.core_ptr.initialize();
        inst.video_ptr.initialize();

        std::ifstream config_file;
        config_file.open(inst.config_path.s_str());
        inst.initialize_resource(config_file);
        config_file.close();
    }
    void config::initialize_resource(std::ifstream& config_file) {
        string line;
        config_file >> line;
        while (line != u8"[resource]") {
            config_file >> line;
        }

        string resource_type;
        string resource_path;
        config_file >> resource_type;
        config_file >> resource_path;
        while (resource_type != u8"" && resource_path != u8"") {
            resource_path_map.add(resource_type, resource_path);
            config_file >> resource_type;
            config_file >> resource_path;
        }
    }
    template<class type_name>
    string config::resource_path() {
        return resource_path_map[class_name<type_name>()];
    }
    slave_ptr<core_config>& config::core() {
        config& inst = config::get_inst();
        return inst.core_ptr.create_slave_ptr();
    }
    slave_ptr<video_config>& config::video() {
        config& inst = config::get_inst();
        return inst.video_ptr.create_slave_ptr();
    }
    config& config::get_inst() {
        static config inst;
        return inst;
    }
}
