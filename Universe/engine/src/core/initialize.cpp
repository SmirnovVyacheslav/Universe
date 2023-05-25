// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "initialize.h"
#include "config.h"
#include "src/platform/api/video.h"
#include "src/gri/gri.h"


namespace engine {
    void initialize() {
        config::initialize();
        //video::initialize();
        t_gri::smf_c_gri();
    }
    void terminate() {
    }
}
