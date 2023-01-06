// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>

#include "src/core/data_type/std.h"
#include "src/core/data_type/string.h"
#include "src/core/data_type/map.h"
#include "src/core/memory/smart_ptr.h"


namespace engine {
    struct core_config {
        string window_name = u8"Engine";
    };
    struct video_config {
        int_32 window_width = 800;
        int_32 window_height = 600;
        int_32 refresh_rate = 60;
    };
    struct resource_config {
        string mesh_path = u8"game/resource/mesh";
        string shader_path = u8"game/resource/shader";
        string model_path = u8"game/resource/model";
        string scene_path = u8"game/resource/scene";
    };


    class config {
        public:
            static void initialize();
            template<class type_name>
            static string resource_path();
            static slave_ptr<core_config>& core();
            static slave_ptr<video_config>& video();
        private:
            const string config_path = u8"game/config/game.config";
            map<string, string> resource_path_map;
            lead_ptr<core_config> core_ptr;
            lead_ptr<video_config> video_ptr;

            config() = default;
            config(config&& src) = delete;
            config(const config& src) = delete;

            static config& get_inst();
            void initialize_resource(std::ifstream& config_file);

            config& operator=(config&& src) = delete;
            config& operator=(const config& src) = delete;

            ~config() = default;
    };
}
