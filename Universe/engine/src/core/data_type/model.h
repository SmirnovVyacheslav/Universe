// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "mesh.h"
#include "shader.h"
#include "src/core/memory/smart_ptr.h"
#include <iostream>


namespace engine {
    class model {
        friend std::istream& operator>>(std::istream& in_stream, model& model_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const model& model_obj);
        public:
            model() = default;
            model(model&& src) = default;
            model(const model& src) = default;

            model& operator=(model&& src) = default;
            model& operator=(const model& src) = default;

            ~model() = default;
        private:
            slave_ptr<mesh_tmp> model_mesh;
            slave_ptr<shader> model_shader;
    };
}
