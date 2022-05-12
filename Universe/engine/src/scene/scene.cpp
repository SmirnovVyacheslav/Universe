// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "scene.h"

namespace engine
{
    scene scene::inst = scene();


    void scene::add_object()
    {
        square = new object;
    }

    object* scene::get_object()
    {
        return square;
    }
}
