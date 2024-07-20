// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_event.h"


#ifndef ENGINE_CORE_EVENT_API
#define ENGINE_CORE_EVENT_API

namespace engine::core::event
{
    void init();

    void add(obj& item);
    void handle();

    void term();
}

#endif
