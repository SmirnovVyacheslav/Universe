// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "shader.h"


namespace engine {
    std::istream& operator>>(std::istream& in_stream, shader& shader_obj) {
        in_stream >> shader_obj.code;
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const shader& shader_obj) {
        return out_stream;
    }
}
