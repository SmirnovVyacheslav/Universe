// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

#include "string.h"


namespace engine
{
    struct graphics_settings
    {
        string window_name = string(std::u8string(u8"Engine"));

        std::int32_t window_width = 800;
        std::int32_t window_height = 600;

        std::int32_t refresh_rate = 60;
    };


    class config
    {
    public:
        static config inst;

        static const graphics_settings& get_graphics_settings();
        static void initialize();

    private:
        graphics_settings* graphics_settings_inst;

        config() = default;
        ~config() = default;
    };
}
#endif
