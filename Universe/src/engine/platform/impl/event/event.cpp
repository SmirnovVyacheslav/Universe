// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/platform/api/event.h"

#include "engine/core/def/class_format.h"
#include "engine/core/control/api_control.h"
#include "engine/platform/impl/event/queue.h"
#include "engine/platform/impl/event/win32/event.h"


namespace engine::platform::event
{
    queue* queue_inst = nullptr;


    void init()
    {
        queue_inst = new queue;
    }

    void term()
    {
        delete queue_inst;
    }

    void add(event_item item)
    {
        queue_inst->add(item);
    }

    void handle()
    {
        win32::handle();

        event_item item = queue_inst->get();
        if (item.exit)
        {
            core::control::stop();
        }
    }
}
