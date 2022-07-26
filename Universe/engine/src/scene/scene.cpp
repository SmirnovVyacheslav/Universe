// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "scene.h"


namespace engine {
    scene scene::inst = scene();


    void scene::add_object() {
        square = new object;
    }
    object* scene::get_object() {
        return square;
    }
}
