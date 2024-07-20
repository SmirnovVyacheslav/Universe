// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_control.h"


#ifndef ENGINE_CORE_CONTROL_API
#define ENGINE_CORE_CONTROL_API

namespace engine::core::control
{
    void start();
    bool status();
    void stop();
}

#endif
