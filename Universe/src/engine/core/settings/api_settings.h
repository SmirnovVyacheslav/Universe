// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_api_settings.h"


#ifndef ENGINE_CORE_SETTINGS_API
#define ENGINE_CORE_SETTINGS_API

namespace engine::core::settings
{
    void init();

    obj& get();

    void term();
}

#endif
