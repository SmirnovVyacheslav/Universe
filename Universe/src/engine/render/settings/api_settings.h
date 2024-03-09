// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_settings.h"


namespace engine::render::settings
{
    void init();
    void term();

    obj& get();
}
