// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/def/abstract.h"

#include "engine/render/mesh/obj_mesh.h"
#include "engine/render/shader/obj_shader.h"


namespace engine::render::device
{
    class obj
    {
        abstract

        virtual void draw(mesh::obj& mesh_obj, shader::obj& shader_obj) = 0;
    };
}
