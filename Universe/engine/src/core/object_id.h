// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef OBJECT_ID_H
#define OBJECT_ID_H

#include "src/platform/container.h"


namespace engine
{
    class object_id
    {
    public:
        static object_id inst;

        int get_object_id();

    private:
        object_id() = default;
        ~object_id() = default;

        int next_id;
    };
}
#endif
