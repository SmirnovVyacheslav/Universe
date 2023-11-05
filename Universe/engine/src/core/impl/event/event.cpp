// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/api/event.h"

#include "src/core/api/control.h"


namespace engine::core::event
{
    void handle()
    {
        control::stop();
    }
}
