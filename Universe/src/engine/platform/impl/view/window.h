// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/core/def/abstract_class.h"


namespace engine::platform::view
{
    abstract_class window
    {
        abstract_def(window)

        virtual void* id() = 0;
    };
}
