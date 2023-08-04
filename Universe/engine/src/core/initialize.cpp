// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/initialize.h"
#include "src/core/config.h"
#include "src/render/api.h"


namespace engine
{
    void initialize()
    {
        config::initialize();
        render::api_t::initialize();
    }

    void terminate()
    {}
}
