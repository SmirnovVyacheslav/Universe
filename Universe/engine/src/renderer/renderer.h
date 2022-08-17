// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class renderer {
        public:
            static void render();
        private:
            static renderer inst;

            renderer() = default;
            ~renderer() = default;
    };
}
