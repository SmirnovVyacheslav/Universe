// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/config.h"
#include "src/core/data_type/string.h"
#include "src/core/memory/smart_ptr.h"


namespace engine {
    namespace platform {
        class window_impl;


        class window {
            public:
                static void create_window();
                static void* id();
            private:
                static window inst;
                lead_ptr<window_impl> impl;

                window() = default;
                ~window() = default;
                window(window&& src) = delete;
                window(const window& src) = delete;
                window& operator=(window&& src) = delete;
                window& operator=(const window& src) = delete;
        };
    }
}
