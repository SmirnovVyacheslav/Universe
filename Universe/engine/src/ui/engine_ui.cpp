// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine_ui.h"

#include "src/core/initialize.h"


namespace engine::ui
{
    engine_ui::engine_ui()
    {
        initialize();
    }

    engine_ui::~engine_ui()
    {
        terminate();
    }
}
