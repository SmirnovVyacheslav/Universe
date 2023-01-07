// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

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
        std::string std_line;
        std::getline(config_file, std_line);
        line = std_line;
        while (line != u8"[resource]") {
            std::getline(config_file, std_line);
            line = std_line;
        }

        string resource_type;
        string resource_path;
        std::istringstream input;
        std::getline(config_file, std_line);
        line = std_line;
        while (line != u8"[end]") {
            input.str(std_line);
            input >> resource_type >> resource_path;
            resource_path_map.add(resource_type, resource_path);
            std::getline(config_file, std_line);
            line = std_line;
        }
    }
    template<typename T>
    string config::resource_path() {
        return resource_path_map[T::name()];
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
