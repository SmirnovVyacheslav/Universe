// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_impl_font.h"

#ifndef ENGINE_RENDER_FONT_IMPL
#define ENGINE_RENDER_FONT_IMPL

namespace engine::render::font
{
    struct char_data
    {
        int16 x = 0;
        int16 y = 0;
        int16 w = 0;
        int16 h = 0;
        int16 ox = 0;
        int16 oy = 0;
        int16 ax = 0;
    };

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
        uint16 tex_width = 0;
        uint16 tex_height = 0;
        map<uint16, char_data> char_map;
    };
}

#endif
