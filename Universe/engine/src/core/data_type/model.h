// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <iostream>

#include "base_resource.h"
#include "mesh.h"
#include "shader.h"
#include "string.h"
#include "src/core/memory/smart_ptr.h"


namespace engine {
    class model : public base_resource {
    public:
        model() = default;
        model(model&& src) = default;
        model(const model& src) = default;

        static string name();

        void load(string file);
        void initialize();
        void render();

        model& operator=(model&& src) = default;
        model& operator=(const model& src) = default;

        ~model() = default;
    private:
        slave_ptr<mesh> model_mesh;
        slave_ptr<shader> model_shader;

        friend std::istream& operator>>(std::istream& in_stream, model& model_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const model& model_obj);
    };
}
