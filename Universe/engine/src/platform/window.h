// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/memory/smart_ptr.h"


namespace engine {
    namespace platform {
        class window {
        public:
            static void create_window();
            static void* id();
        private:
            class window_impl;

            static window inst;
            lead_ptr<window_impl> impl;

            window();
            window(window&& src) = delete;
            window(const window& src) = delete;

            window& operator=(window&& src) = delete;
            window& operator=(const window& src) = delete;

            ~window();
        };
    }
}
