// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/resource/mesh.h"


namespace engine {
    class object {
    public:
        object();
        object(object&& src) = default;
        object(const object & src) = delete;

        mesh& get_mesh();

        object& operator=(object&& src) = default;
        object& operator=(const object& src) = delete;

        ~object() = default;
    private:
        int id;
        mesh square;
    };
}
