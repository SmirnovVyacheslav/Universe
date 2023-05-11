// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#include "src/gsi/gsi.h"

namespace engine {
    gsi gsi::inst = gsi();

    void gsi::init() {
        //
    }
    void gsi::smf_c_gsi() {
        inst.mo_gdi.mf_c_gdi(&inst.mo_gdi_cfg);
    }
    void gsi::smf_d_gsi() {
        inst.mo_gdi.mf_d_gdi();
    }
}
