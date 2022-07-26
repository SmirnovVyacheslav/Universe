// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class render {
        public:
            static void start_render();
        private:
            static render inst;

            render() = default;
            ~render() = default;
    };
}
