// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include <iostream>
#include <fstream>
#include <filesystem>

#include "src/platform/api/video.h"

#include "shader.h"


namespace engine {
    string shader::name() {
        return u8"shader";
    }
    void shader::load(string file) {
        std::ifstream input_stream;
        input_stream.open(file.u8_str());
        input_stream >> *this;
        input_stream.close();
    }
    void shader::initialize() {
    }
    std::istream& operator>>(std::istream& in_stream, shader& shader_obj) {
        shader_obj.code = string(std::string(std::istreambuf_iterator<char>(in_stream), std::istreambuf_iterator<char>()));
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const shader& shader_obj) {
        return out_stream;
    }
}
