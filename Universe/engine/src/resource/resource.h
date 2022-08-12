// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/map.h"
#include "src/core/data_type/mesh.h"
#include "src/core/data_type/shader.h"
#include "src/core/data_type/model.h"
#include "src/core/data_type/string.h"
#include "src/core/memory/smart_ptr.h"


namespace engine {
    class resource {
        public:
            static void load();
            static slave_ptr<mesh_tmp>& mesh_prt(const string name);
            static slave_ptr<shader>& shader_prt(const string name);
            static slave_ptr<model>& model_prt(const string name);
        private:
            static resource inst;
            map<string, lead_ptr<mesh_tmp>> mesh_map;
            map<string, lead_ptr<shader>> shader_map;
            map<string, lead_ptr<model>> model_map;

            resource() = default;
            ~resource() = default;
            resource(resource&& src) = delete;
            resource(const resource& src) = delete;

            resource& operator=(resource&& src) = delete;
            resource& operator=(const resource& src) = delete;

            void load_mesh();
            void load_shader();
    };
}
