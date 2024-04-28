// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_device.h"

#include "engine/render/mesh/obj_mesh.h"
#include "engine/render/shader/obj_shader.h"
#include "engine/var/string.h"


namespace engine::render::device
{
    void init();

    void draw(mesh::obj& mesh_obj, shader::obj& shader_obj);
    string type();

    void term();
}
