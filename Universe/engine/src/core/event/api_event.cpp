// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/event/api_event.h"
#include "src/platform/api/event.h"


namespace engine::core::event
{
    void handle()
    {
        platform::event::handle();
    }
}
