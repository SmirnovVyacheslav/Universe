// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "render.h"
#include "src/platform/api/video.h"
#include "src/platform/platform_def.h"
#ifdef WINDOWS
#include <windows.h>


namespace engine {
    render render::inst = render();


    void render::start_render() {
        video::create_device();

        MSG msg = { 0 };
        while (WM_QUIT != msg.message)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                video::render();
            }
        }
    }
}
#endif
