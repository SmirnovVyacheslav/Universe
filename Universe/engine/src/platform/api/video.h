// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class video_api {
        public:
            virtual void create_device() = 0;
        protected:
            video_api() = default;
            ~video_api() = default;
    };
    class video {
        public:
            video() = default;
            ~video() = default;

            void create_device();
        private:
            //
    };
}
