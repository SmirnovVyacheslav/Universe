// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_device.h"

#include "engine/var/string.h"


namespace engine::render::device
{
    void init();

    void draw();
    string type();

    void term();
}
