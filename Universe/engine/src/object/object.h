// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/resource/mesh.h"


namespace engine {
    class object {
        public:
            object();
            ~object() = default;
            mesh& get_mesh();
        private:
            int id;
            mesh square;
    };
}
