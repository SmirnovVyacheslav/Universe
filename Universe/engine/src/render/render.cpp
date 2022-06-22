// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "render.h"
#include "src/platform/api/video.h"


namespace engine {
    render render::inst = render();


    void render::start_render() {
        video::create_device();
        while (true) {
            video::render();
        }
    }
}
