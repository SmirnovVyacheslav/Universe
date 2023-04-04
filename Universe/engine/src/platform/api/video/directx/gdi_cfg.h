#pragma once
// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/string.h"
#include "src/core/data_type/matrix_4.h"
#include "src/platform/platform_def.h"
#include "src/platform/api/video.h"

#ifdef WINDOWS
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>

// t = type
// r = reference
// p = pointer
// o = object
// c = const
// m = member
// g = global
// _c_ = construct
// _d_ = destroy

// gdi - graphics device instance
class t_gdi_cfg {
public:
    t_gdi_cfg() = default;
    t_gdi_cfg(t_gdi_cfg&& r_src) = default;
    t_gdi_cfg(const t_gdi_cfg& cr_src) = default;
    ~t_gdi_cfg() = default;

public:
    t_gdi_cfg& operator=(t_gdi_cfg&& r_src) = default;
    t_gdi_cfg& operator=(const t_gdi_cfg& cr_src) = default;

public:
    t_swap_chain_cfg mo_swap_chain_cfg;
    t_device_cfg mo_device_cfg;
    t_depth_stencil_cfg mo_depth_stencil_cfg;
};

#else

#endif