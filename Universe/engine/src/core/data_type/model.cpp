// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "model.h"
#include "src/resource/resource.h"


namespace engine {
    std::istream& operator>>(std::istream& in_stream, model& model_obj) {
        string str;
        in_stream >> str;
        if (str != string(u8"mesh")) {
            throw std::invalid_argument("Incorrect file format");
        }
        in_stream >> str;
        // model_obj.model_mesh = resource::mesh_prt(str);

        in_stream >> str;
        if (str != string(u8"shader")) {
            throw std::invalid_argument("Incorrect file format");
        }
        in_stream >> str;
        // model_obj.model_shader = resource::shader_prt(str);

        in_stream >> str;
        if (str != string(u8"color")) {
            throw std::invalid_argument("Incorrect file format");
        }
        in_stream >> str;

        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const model& model_obj) {
        return out_stream;
    }
}
