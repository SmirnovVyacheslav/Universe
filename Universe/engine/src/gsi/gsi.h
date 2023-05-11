// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/gdi/gdi.h"
#include "src/gdi/gdi_cfg.h"


// Graphics System interface
namespace engine {
    class gsi {
        public:
        static void init();
        static void smf_c_gsi();
        static void smf_d_gsi();
        private:
        static gsi inst;

        gsi() = default;
        gsi(gsi&& src) = default;
        gsi(const gsi& src) = default;

        gsi& operator=(gsi&& src) = default;
        gsi& operator=(const gsi& src) = default;

        ~gsi() = default;

        t_gdi mo_gdi;
        t_gdi_cfg mo_gdi_cfg;
    };
}
