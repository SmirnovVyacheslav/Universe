// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "src/core/initialize.h"

#include "engine_ui.h"


namespace engine {
    namespace ui {
        engine_ui::engine_ui() {
            initialize();
        }
        engine_ui::~engine_ui() {
            terminate();
        }
    }
}
