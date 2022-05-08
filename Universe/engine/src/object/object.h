// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "src/platform/std_types.h"


namespace engine
{
    class object
    {
    public:
        object() = default;
        ~object() = default;

    private:
        integer id;
    };
}
#endif
