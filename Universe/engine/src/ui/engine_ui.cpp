// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine_ui.h"
#include "src/core/initialize.h"
#include "src/scene/scene.h"
#include "src/render/render.h"


namespace engine {
    namespace ui {
        engine_ui::engine_ui() {
            initialize();
        }
        engine_ui::~engine_ui() {
            terminate();
        }
        void engine_ui::add_object() {
            engine::scene::inst.add_object();
        }
        void engine_ui::start_render() {
            engine::render::start_render();
        }
    }
}
