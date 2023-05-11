// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/gdi/device.h"
#include "src/platform/gdi/direct_x/device_direct_x.h"


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
    t_device* gf_c_device(const t_gdi_cfg& cr_dgi_cfg) {
        return new t_device_direct_x();
    }
}
