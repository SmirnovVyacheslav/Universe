// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/gdi/gdi.h"


namespace engine {
    void t_gdi::mf_c_gdi(const t_gdi_cfg* cr_gdi_cfg) {
        mp_device = gf_c_device(*cr_gdi_cfg);
    }
    void t_gdi::mf_d_gdi() {
        //
    }
}
