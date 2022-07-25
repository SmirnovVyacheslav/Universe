// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "mesh.h"


namespace engine {
    uint_32 mesh::size() {
        return index_array.size();
    }
    vertex& mesh::vertices() {
        return vertex_array[0];
    }
    uint_16& mesh::indices() {
        return index_array[0];
    }
}
