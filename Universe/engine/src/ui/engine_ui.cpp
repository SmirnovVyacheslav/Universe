// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "src/core/initialize.h"
#include "src/renderer/renderer.h"
#include "src/resource/resource.h"

#include "engine_ui.h"


namespace engine {
    namespace ui {
        engine_ui::engine_ui() {
            initialize();
        }
        engine_ui::~engine_ui() {
            terminate();
        }
        void engine_ui::initialize_resource() {
            resource::initialize();
        }
        void engine_ui::render() {
            engine::renderer::render();
        }
    }
}
