// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "model.h"
#include "src/core/data_type/array.h"
#include "src/core/memory/smart_ptr.h"
#include <iostream>


namespace engine {
    class scene_tmp {
        friend std::istream& operator>>(std::istream& in_stream, scene_tmp& scene_obj);
        friend std::ostream& operator<<(std::ostream& out_stream, const scene_tmp& scene_obj);
    public:
        scene_tmp() = default;
        scene_tmp(scene_tmp&& src) = default;
        scene_tmp(const scene_tmp& src) = default;

        scene_tmp& operator=(scene_tmp&& src) = default;
        scene_tmp& operator=(const scene_tmp& src) = default;

        ~scene_tmp() = default;
    private:
        array<slave_ptr<model>> model_array;
    };
}
