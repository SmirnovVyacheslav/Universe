// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_event.h"

#include "engine/src/platform/api/event.h"



namespace engine::core::event
{
    void handle()
    {
        platform::event::handle();
    }
}
