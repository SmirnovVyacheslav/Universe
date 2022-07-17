// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <cstdint>
#include "src/core/data_type/string.h"
#include "src/core/memory/smart_ptr.h"


namespace engine {
    struct core_config {
        string window_name = string(u8"Engine");
    };
    struct video_config {
        std::int32_t window_width = 800;
        std::int32_t window_height = 600;
        std::int32_t refresh_rate = 60;
    };
    class config {
        public:
            static void initialize();
            static slave_ptr<core_config>& core();
            static slave_ptr<video_config>& video();
        private:
            static config inst;
            lead_ptr<core_config> core_ptr;
            lead_ptr<video_config> video_ptr;

            config() = default;
            ~config() = default;
            config(config&& src) = delete;
            config(const config& src) = delete;
            config& operator=(config&& src) = delete;
            config& operator=(const config& src) = delete;
    };
}
