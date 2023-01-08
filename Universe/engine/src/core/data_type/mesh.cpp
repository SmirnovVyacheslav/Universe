// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "mesh.h"
#include "string.h"


namespace engine {
    string mesh::name() {
        return u8"mesh";
    }
    uint_32 mesh::size() {
        return index_array.size();
    }
    vertex_tmp& mesh::vertices() {
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
            mesh_obj.vertex_array.append(vertex_tmp(vertex_vec, vector_4(0.0f, 0.0f, 1.0f, 1.0f)));
        }

        in_stream >> str;
        if (str != string(u8"indices")) {
            throw std::invalid_argument("Incorrect file format");
        }

        uint_32 indices_num = 0;
        in_stream >> indices_num;
        uint_16 index;
        for (uint_32 i = 0; i < indices_num; ++i) {
            in_stream >> index;
            mesh_obj.index_array.append(index);
        }

        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const mesh& mesh_obj) {
        return out_stream;
    }
}
