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


    void read_vertices(std::istream& in_stream, mesh& mesh_obj) {
        string str;
        in_stream >> str;
        if (str != string(u8"vertices")) {
            throw std::invalid_argument("Incorrect file format");
        }

        uint_32 vertices_num = 0;
        in_stream >> vertices_num;
        for (uint_32 i = 0; i < vertices_num; ++i) {
            //
        }
    }
    void read_indices(std::istream& in_stream, mesh& mesh_obj) {
        //
    }
    std::istream& operator>>(std::istream& in_stream, mesh& mesh_obj) {
        read_vertices(in_stream, mesh_obj);
        read_indices(in_stream, mesh_obj);
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const mesh& mesh_obj) {
        return out_stream;
    }
}
