// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "config.h"


namespace engine {
    config config::inst = config();


    void config::initialize() {
        inst.core_ptr.initialize();
        inst.video_ptr.initialize();
    }
    const slave_ptr<core_config>& config::core() {
        return config::inst.core_ptr.create_slave_ptr();
    }
    const slave_ptr<video_config>& config::video() {
        return config::inst.video_ptr.create_slave_ptr();
    }
}
