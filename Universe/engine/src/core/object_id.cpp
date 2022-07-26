// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "object_id.h"


namespace engine {
    object_id object_id::inst = object_id();


    int object_id::get_object_id() {
        return next_id++;
    }
}
