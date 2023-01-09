// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <iostream>

#include "base_resource.h"
#include "model.h"
#include "string.h"
#include "src/core/data_type/array.h"
#include "src/core/memory/smart_ptr.h"



namespace engine {
    class scene : public base_resource {
    public:
        scene() = default;
        scene(scene&& src) = default;
        scene(const scene& src) = default;

        static string name();

        void load(string file);
        void initialize();
        void render();

        scene& operator=(scene&& src) = default;
        scene& operator=(const scene& src) = default;

        ~scene() = default;
    private:
        array<slave_ptr<model>> model_array;

        friend std::istream& operator>>(std::istream& in_stream, scene& scene_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const scene& scene_obj);
    };
}
