// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/gdi/gdi_cfg.h"


namespace engine
{
    // interface t_device
    struct t_device
    {
        static t_device* smf_c_directx(const t_gdi_cfg& cr_dgi_cfg);

        virtual ~t_device() = default; //pvf;
    };
}