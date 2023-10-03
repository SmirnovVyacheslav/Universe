// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/core_api.h"

#include "src/core/initialize.h"
#include "src/core/config.h"
#include "src/render/api.h"
#include "src/platform/platform.h"


namespace engine
{
    void initialize()
    {
        platform::core::init();

        config::initialize();
        platform::init();
        render::api_t::initialize();
    }

    void terminate()
    {
        platform::core::term();
    }
}
