// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/map.h"
#include "src/core/data_type/mesh.h"
#include "src/core/data_type/shader.h"
#include "src/core/data_type/model.h"
#include "src/core/data_type/scene.h"
#include "src/core/data_type/string.h"
#include "src/core/memory/smart_ptr.h"


namespace engine {
    class resource {
    public:
        static void initialize();
        static slave_ptr<mesh>& mesh_prt(const string name);
        static slave_ptr<shader>& shader_prt(const string name);
        static slave_ptr<model>& model_prt(const string name);
        static slave_ptr<scene>& scene_prt(const string name);
    private:
        static resource inst;
        map<string, lead_ptr<mesh>> mesh_map;
        map<string, lead_ptr<shader>> shader_map;
        map<string, lead_ptr<model>> model_map;
        map<string, lead_ptr<scene>> scene_map;

        resource() = default;
        resource(resource&& src) = delete;
        resource(const resource& src) = delete;

        void load_mesh();
        void load_shader();
        void load_model();
        void load_scene();

        resource& operator=(resource&& src) = delete;
        resource& operator=(const resource& src) = delete;

        ~resource() = default;
    };
}
