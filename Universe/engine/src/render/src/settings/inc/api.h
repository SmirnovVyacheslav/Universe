// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/src/settings/inc/obj.h"


namespace engine::render::settings
{
    void init();
    void term();

    obj& get();
}
