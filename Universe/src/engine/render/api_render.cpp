// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_render.h"

#include "camera/api_camera.h"
#include "device/api_device.h"
#include "index/api_index.h"
#include "mesh/api_mesh.h"
#include "settings/api_settings.h"
#include "shader/api_shader.h"
#include "vertex/api_vertex.h"


namespace engine::render
{
    void init()
    {
        settings::init();
        camera::init();
        device::init();
        index::init();
        vertex::init();
        shader::init();
        mesh::init();
    }

    void draw()
    {
        mesh::obj& mesh_obj = mesh::add(u8"res/game/mesh/cube.mesh");
        device::draw();
    }

    void term()
    {
        mesh::term();
        shader::term();
        vertex::term();
        index::term();
        device::term();
        camera::term();
        settings::term();
    }
}
