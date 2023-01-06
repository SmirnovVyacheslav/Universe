// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "src/core/object_id.h"

#include "object.h"


namespace engine {
    object::object() :
        id(object_id::inst.get_object_id()) {
    }
    mesh& object::get_mesh() {
        return square;
    }
}
