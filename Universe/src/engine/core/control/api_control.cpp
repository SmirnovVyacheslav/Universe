// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_control.h"


namespace engine::core::control
{
    bool exec_status = false;


    void start()
    {
        exec_status = true;
    }

    bool status()
    {
        return exec_status;
    }

    void stop()
    {
        exec_status = false;
    }
}
