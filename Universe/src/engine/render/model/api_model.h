// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_model.h"


#ifndef ENGINE_RENDER_MODEL_API
#define ENGINE_RENDER_MODEL_API

namespace engine::render::model
{
    void init();

    obj& add(string name);

    void term();
}

#endif
