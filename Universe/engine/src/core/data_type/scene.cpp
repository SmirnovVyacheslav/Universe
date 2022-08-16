// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "scene.h"
#include "src/resource/resource.h"


namespace engine {
    std::istream& operator>>(std::istream& in_stream, scene_tmp& scene_obj) {
        string str;
        in_stream >> str;
        if (str != string(u8"model")) {
            throw std::invalid_argument("Incorrect file format");
        }
        in_stream >> str;
        while (str != u8"") {
            scene_obj.model_array.append(resource::model_prt(str));
            in_stream >> str;
        }

        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const scene_tmp& scene_obj) {
        return out_stream;
    }
}
