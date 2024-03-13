// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/def/platform.h"
#include "engine/platform/impl/event/win32/event.h"

#ifdef windows
#include <windows.h>
#endif


namespace engine::platform::event::win32
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

    #else

    void handle()
    {}

    #endif
}
