// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_settings.h"


#ifndef ENGINE_RENDER_SETTINGS_API
#define ENGINE_RENDER_SETTINGS_API

namespace engine::render::settings
{
    void init();

    obj& get();

    void term();
}

#endif
