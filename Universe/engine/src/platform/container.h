// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include "src/platform/toolkit/stl/stl.h"


namespace engine
{
    namespace platform
    {
        template <class key, class value>
        class map
        {
        private:
            stl::map<key, value> impl;
        };
    }
}
#endif
