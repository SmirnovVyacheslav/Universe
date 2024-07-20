// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_impl_event.h"


namespace engine::core::event::impl
{
#ifdef windows

    void handle()
    {
        MSG message = { 0 };
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

#endif
}
