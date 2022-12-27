// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "string.h"
#include "class_name.h"
#include <iostream>


namespace engine {
    class shader {
        friend std::istream& operator>>(std::istream& in_stream, shader& shader_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const shader& shader_obj);
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
    };


    template<>
    string class_name<shader>();
}
