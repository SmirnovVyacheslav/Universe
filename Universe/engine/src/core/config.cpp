// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "config.h"


namespace engine {
    config config::inst = config();


    void config::initialize() {
        inst.graphics_settings_inst.initialize();
    }
    slave_ptr<graphics_settings>& config::get_graphics_settings() {
        return config::inst.graphics_settings_inst.create_slave_ptr();
    }
}
