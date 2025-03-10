// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_core.h"


namespace engine::core
{
    void init()
    {
        settings::init();
        event::init();
        view::init();
        render::init();
    }

    void exec()
    {
        control::start();

        while (control::status())
        {
            event::handle();
            render::draw();
            //std::exit(-1);
        }
    }

    void term()
    {
        render::term();
        view::term();
        event::term();
        settings::term();
    }
}
