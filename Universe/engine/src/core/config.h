// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/std.h"
#include "src/core/data_type/string.h"
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
    };
    class config {
        public:
            static void initialize();
            static slave_ptr<core_config>& core();
            static slave_ptr<video_config>& video();
            static slave_ptr<resource_config>& resource();
        private:
            static config inst;
            lead_ptr<core_config> core_ptr;
            lead_ptr<video_config> video_ptr;
            lead_ptr<resource_config> resource_ptr;

            config() = default;
            ~config() = default;
            config(config&& src) = delete;
            config(const config& src) = delete;
            config& operator=(config&& src) = delete;
            config& operator=(const config& src) = delete;
    };
}
