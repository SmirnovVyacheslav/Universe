// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_settings.h"


#ifndef ENGINE_CORE_SETTINGS_API
#define ENGINE_CORE_SETTINGS_API

namespace engine::core::settings
{
    void init();

    obj& get();

    void term();
}

#endif
