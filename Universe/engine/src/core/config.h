// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>

#include "src/core/type/std.h"
#include "src/core/type/string.h"
#include "src/core/type/map.h"
#include "src/core/memory/smart_ptr.h"


namespace engine {
    struct core_config {
        string window_name = u8"Engine";
    };
    struct video_config {
        int32 window_width = 800;
        int32 window_height = 600;
        int32 refresh_rate = 60;
    };


    class config {
        public:
            static void initialize();
            template<typename T>
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


    template<typename T>
    string config::resource_path() {
        config& inst = config::get_inst();
        return inst.resource_path_map[T::name()];
    }
}
