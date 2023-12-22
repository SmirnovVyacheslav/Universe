// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/platform/api/render/shader.h"


namespace engine::platform::render
{
    abstract_class device
    {
        abstract_def(device)

        virtual void draw() = 0;

        virtual shader::shader* init_shader(string file);
    };
}
