// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/array.h"
#include "src/core/memory/smart_ptr.h"
#include <cstdint>


namespace engine {
    class video_api {
        public:
            video_api(video_api&& src) = delete;
            video_api(const video_api& src) = delete;

            virtual bool available() = 0;
            virtual void create_device() = 0;
            virtual void render() = 0;

            video_api& operator=(video_api&& src) = delete;
            video_api& operator=(const video_api& src) = delete;

            ~video_api() = default;
        protected:
            video_api() = default;
    };
    class video {
        public:
            video(video&& src) = delete;
            video(const video& src) = delete;

            static void initialize();
            // static void* compile_shader();
            static void render();

            video& operator=(video&& src) = delete;
            video& operator=(const video& src) = delete;
        private:
            static video inst;
            std::int32_t actual_api_index = 0;
            array< lead_ptr<video_api> > api_list;

            video() = default;

            void create_device();
            void set_actual_api();

            ~video() = default;
    };
}
