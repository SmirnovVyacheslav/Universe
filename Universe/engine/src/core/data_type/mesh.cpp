// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "mesh.h"
#include "string.h"


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


    std::istream& operator>>(std::istream& in_stream, mesh& mesh_obj) {
        string str;
        in_stream >> str;
        if (str != string(u8"vertices")) {
            throw std::invalid_argument("Incorrect file format");
        }

        uint_32 vertices_num = 0;
        in_stream >> vertices_num;
        vector_3 vertex_vec;
        for (uint_32 i = 0; i < vertices_num; ++i) {
            in_stream >> vertex_vec;
            mesh_obj.vertex_array.append(vertex(vertex_vec, vector_4(0.0f, 0.0f, 1.0f, 1.0f)));
        }
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const mesh& mesh_obj) {
        return out_stream;
    }
}
