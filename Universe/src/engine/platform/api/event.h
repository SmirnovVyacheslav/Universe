// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine::platform::event
{
    struct event_item
    {
        bool exit = false;
    };

    void init();
    void term();

    void add(event_item item);
    void handle();
}
