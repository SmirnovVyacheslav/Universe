// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_model.h"

#include "engine/var/string.h"


namespace engine::render::model
{
    void init();

    obj& add(string name);

    void term();
}
