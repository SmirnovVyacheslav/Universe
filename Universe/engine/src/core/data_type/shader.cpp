// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/api/video.h"

#include "shader.h"


namespace engine {
    std::istream& operator>>(std::istream& in_stream, shader& shader_obj) {
        shader_obj.code = string(std::string(std::istreambuf_iterator<char>(in_stream), std::istreambuf_iterator<char>()));
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const shader& shader_obj) {
        return out_stream;
    }


    template<>
    string class_name<shader>() {
        return "shader";
    }
}
