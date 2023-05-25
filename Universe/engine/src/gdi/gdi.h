// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/defines.h"
#include "src/gdi/gdi_cfg.h"


namespace engine
{
    interface t_gdi //graphics device interface
    {
        static t_gdi* smf_c_gdi(const t_gdi_cfg* cr_gdi_cfg);
        //static void smf_d_gdi();

        virtual ~t_gdi() = default; //pvf;
    };
}
