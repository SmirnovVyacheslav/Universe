// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "src/platform/platform_def.h"

#pragma once
#ifdef WINDOWS
#ifndef STL_H
#define STL_H

#include <vector>
#include <unordered_map>


namespace engine
{
    namespace platform
    {
        namespace stl
        {
            template <class key, class value>
            class map
            {
            private:
                std::unordered_map<key, value> impl;
            };


            template <class type>
            class vector
            {
            private:
                std::vector<type> impl;
            };
        }
    }
}
#endif
#endif
