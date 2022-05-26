// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "initialize.h"
#include "config.h"


namespace engine {
    void initialize() {
        config::initialize();
    }
    void terminate() {
        //
    }
}
