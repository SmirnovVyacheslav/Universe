// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "initialize.h"
#include "config.h"
#include "src/platform/api/video.h"


namespace engine {
    void initialize() {
        config::initialize();
        video::initialize();
    }
    void terminate() {
    }
}
