// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_indices.h"


#ifndef ENGINE_RENDER_INDICES_API
#define ENGINE_RENDER_INDICES_API

namespace engine::render::indices
{
    void init();

    obj& add(array<uint16> data);

    void term();
}

#endif
