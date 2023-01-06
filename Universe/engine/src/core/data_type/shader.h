// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <iostream>

#include "class_name.h"
#include "string.h"


namespace engine {
    class shader {
    public:
        shader() = default;
        shader(shader&& src) = default;
        shader(const shader& src) = default;

        shader& operator=(shader&& src) = default;
        shader& operator=(const shader& src) = default;

        ~shader() = default;
    private:
        string code;
        void* vertex_shader;
        void* pixel_shader;

        friend std::istream& operator>>(std::istream& in_stream, shader& shader_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const shader& shader_obj);
    };


    template<>
    string class_name<shader>();
}
