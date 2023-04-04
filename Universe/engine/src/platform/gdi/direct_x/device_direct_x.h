// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/gdi/device.h"


// t = type
// r = reference
// p = pointer
// o = object
// c = const
// m = member
// g = global
// _c_ = construct
// _d_ = destroy

namespace engine {
    class t_device_direct_x : public t_device {
    public:
        t_device_direct_x() = default;
        ~t_device_direct_x() = default;

        virtual void mf_c_device();
        virtual void mf_d_device();
    };

    t_device* gf_c_device();
}
