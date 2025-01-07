// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_event.h"


namespace engine::core::event
{
    queue<obj>* queue_inst = nullptr;


    void init()
    {
        term();
        queue_inst = new queue<obj>;
    }

    void add(obj& item)
    {
        queue_inst->add(item);
    }

    void handle()
    {
        impl::handle();

        if (*queue_inst)
        {
            obj item = queue_inst->get();
            if (item.exit)
            {
                core::control::stop();
            }
        }
    }

    void term()
    {
        delete queue_inst;
        queue_inst = nullptr;
    }
}
