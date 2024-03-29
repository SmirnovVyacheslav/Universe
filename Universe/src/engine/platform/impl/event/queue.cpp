// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/platform/api/event.h"

#include "engine/platform/impl/event/queue.h"


namespace engine::platform::event
{
    void queue::add(event_item item)
    {
        this->item = item;
    }

    event_item queue::get()
    {
        return item;
    }
}
