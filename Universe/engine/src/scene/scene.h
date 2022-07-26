// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/object/object.h"


namespace engine {
    class scene {
        public:
            static scene inst;

            void add_object();
            object* get_object();
        private:
            scene() = default;
            ~scene() = default;

            object* square;
    };
}
