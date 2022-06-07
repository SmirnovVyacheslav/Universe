// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <cstdint>
#include "src/core/array.h"
#include "src/core/memory.h"



namespace engine {
    class video_api {
        public:
            video_api() = default;
            ~video_api() = default;
			virtual bool available() = 0;
            virtual void create_device() = 0;
    };
    class video {
        public:
            void initialize();

            void create_device();
        private:
            static video inst;
            std::int32_t actual_api_index;
            array< lead_ptr<video_api> > api_list;

            video() = default;
            ~video() = default;
			void set_actual_api();
    };
}
