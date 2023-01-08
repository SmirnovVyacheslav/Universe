// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "src/resource/resource.h"
#include "src/platform/api/video.h"
#include "src/platform/platform_def.h"

#include "renderer.h"

#ifdef WINDOWS
#include <windows.h>


namespace engine {
    renderer renderer::inst = renderer();


    void renderer::render() {
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
