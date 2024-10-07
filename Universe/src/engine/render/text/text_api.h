// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "text_obj.h"

#ifndef ENGINE_RENDER_TEXT_API
#define ENGINE_RENDER_TEXT_API

namespace engine::render::text
{
    void init();

    obj& add();

    void term();
}

#endif
