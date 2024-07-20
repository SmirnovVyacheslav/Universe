// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_view.h"


#ifndef ENGINE_CORE_VIEW_OBJ
#define ENGINE_CORE_VIEW_OBJ

namespace engine::core::view
{
    class obj
    {
        abstract

        virtual void* id() = 0;
    };
}

#endif
