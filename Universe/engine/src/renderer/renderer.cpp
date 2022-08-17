// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "renderer.h"
#include "src/resource/resource.h"
#include "src/platform/api/video.h"
#include "src/platform/platform_def.h"
#ifdef WINDOWS
#include <windows.h>


namespace engine {
    renderer renderer::inst = renderer();


    void renderer::render() {
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
                resource::scene_prt(u8"scene_01.scene")->render();
                video::render();
            }
        }
    }
}
#endif
