// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "text_obj.h"

#include "engine/render/font/font_api.h"

#ifndef ENGINE_RENDER_TEXT_IMPL
#define ENGINE_RENDER_TEXT_IMPL

namespace engine::render::text
{
    class impl : public obj
    {
    public:
        impl();
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void set();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl() = default;
    private:
        font::obj& font_obj;
    };
}

#endif
