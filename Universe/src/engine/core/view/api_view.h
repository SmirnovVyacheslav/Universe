// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_view.h"


#ifndef ENGINE_CORE_VIEW_API
#define ENGINE_CORE_VIEW_API

namespace engine::core::view
{
    void init();

    obj& get();

    void term();
}

#endif
