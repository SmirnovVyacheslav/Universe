// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine_ui.h"

#include "src/api/core.h"


namespace engine::ui
{
    engine_ui::engine_ui()
    {
        init();
    }

    void engine_ui::exec()
    {
        //
    }

    engine_ui::~engine_ui()
    {
        term();
    }
}
