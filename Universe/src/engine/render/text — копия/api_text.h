// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_text.h"


#ifndef ENGINE_RENDER_TEXT_API
#define ENGINE_RENDER_TEXT_API

namespace engine::render::text
{
    void init();

    obj& add();

    void term();
}

#endif
