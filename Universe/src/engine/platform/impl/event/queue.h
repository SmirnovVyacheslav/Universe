// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/core/def/class_format.h"
#include "engine/platform/api/event.h"


namespace engine::platform::event
{
    class queue
    {
        ____________________public____________________
        queue() = default;
        queue(queue&& src) = delete;
        queue(const queue& src) = delete;

        void add(event_item item);
        event_item get();

        queue& operator=(queue&& src) = delete;
        queue& operator=(const queue& src) = delete;

        ~queue() = default;
        ____________________private___________________
        event_item item;
    };
}
