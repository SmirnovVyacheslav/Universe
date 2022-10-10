// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <cstdint>
#include "src/core/data_type/array.h"
#include "src/core/memory/smart_ptr.h"



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

            static void render();
        private:
            static video inst;
            std::int32_t actual_api_index = 0;
            array< lead_ptr<video_api> > api_list;

            video() = default;
            ~video() = default;
            void create_device();
            void set_actual_api();
    };
}
