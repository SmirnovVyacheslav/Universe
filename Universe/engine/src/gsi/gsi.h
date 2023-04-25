// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#pragma once

// Graphics System interface
namespace engine {
    class gsi {
        public:
        static void init();
        private:
        static gsi inst;

        gsi() = default;
        gsi(gsi&& src) = default;
        gsi(const gsi& src) = default;

        gsi& operator=(gsi&& src) = default;
        gsi& operator=(const gsi& src) = default;

        ~gsi() = default;
    };
}
