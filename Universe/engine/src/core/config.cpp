// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "config.h"


namespace engine {
    config config::inst = config();


    void config::initialize() {
        inst.core_ptr.initialize();
        inst.video_ptr.initialize();
    }
    slave_ptr<core_config>& config::core() {
        return config::inst.core_ptr.create_slave_ptr();
    }
    slave_ptr<video_config>& config::video() {
        return config::inst.video_ptr.create_slave_ptr();
    }
    slave_ptr<resource_config>& config::resource() {
        return config::inst.resource_ptr.create_slave_ptr();
    }
}
