// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/api/view.h"

#include "src/platform/impl/view/window.h"
#include "src/platform/impl/view/win32/window_impl.h"


namespace engine::platform::view
{
    window* window_inst = nullptr;


    void init()
    {
        window_inst = new win32::window_impl();
    }

    void term()
    {
        delete window_inst;
    }

    void* id()
    {
        return window_inst->id();
    }
}
