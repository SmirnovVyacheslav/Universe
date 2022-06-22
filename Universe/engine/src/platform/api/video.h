// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <cstdint>
#include "src/core/array.h"
#include "src/core/memory.h"



namespace engine {
    class video_api {
        public:
            ~video_api() = default;
            virtual bool available() = 0;
            virtual void create_device() = 0;
            virtual void render() = 0;
        protected:
            video_api() = default;
    };
    class video {
        public:
            static void initialize();
            static void create_device();
            static void render();
        private:
            static video inst;
            std::int32_t actual_api_index = 0;
            array< lead_ptr<video_api> > api_list;

            video() = default;
            ~video() = default;
            void set_actual_api();
    };
}
