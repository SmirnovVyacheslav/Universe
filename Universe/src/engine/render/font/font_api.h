// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "font_obj.h"

#include "engine/var/string.h"

#ifndef ENGINE_RENDER_FONT_API
#define ENGINE_RENDER_FONT_API

namespace engine::render::font
{
    void init();

    obj& get(string name);

    void term();
}

#endif
