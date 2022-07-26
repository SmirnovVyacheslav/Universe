// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "object.h"
#include "src/core/object_id.h"


namespace engine {
    object::object() :
        id(object_id::inst.get_object_id()) {
    }
    mesh& object::get_mesh() {
        return square;
    }
}
