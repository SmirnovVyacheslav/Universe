// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/defines.h"

// t = type
// r = reference
// p = pointer
// o = object
// c = const
// m = member
// g = global
// _c_ = construct
// _d_ = destroy

namespace engine
{
    interface t_gri //graphics render interface
    {
        static void smf_c_gri();
        static void smf_d_gri();

        virtual ~t_gri() = default; //pvf;
    };
}
