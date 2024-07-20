// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_core.h"


#ifndef ENGINE_CORE_API
#define ENGINE_CORE_API

namespace engine::core
{
    void init();

    void exec();

    void term();
}

#endif
