// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "font_obj.h"

#include "engine/var/map.h"
#include "engine/var/string.h"

#ifndef ENGINE_RENDER_FONT_IMPL
#define ENGINE_RENDER_FONT_IMPL

namespace engine::render::font
{
    class impl : public obj
    {
    public:
        impl(string name);
        impl(impl&& src) = default;
        impl(const impl& src) = default;

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl() = default;
    private:
        struct char_data
        {
            int16 pos_x = 0;
            int16 pos_y = 0;
            int16 size_w = 0;
            int16 size_h = 0;
            int16 offset_x = 0;
            int16 offset_y = 0;
            int16 advance_x = 0;
        };

        uint16 char_width = 0;
        uint16 char_height = 0;
        map<uint16, char_data> char_map;
    };
}

#endif
