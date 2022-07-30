// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class resource {
        public:
            static void load();
        private:
            static resource inst;

            resource() = default;
            ~resource() = default;
            resource(resource&& src) = delete;
            resource(const resource& src) = delete;

            resource& operator=(resource&& src) = delete;
            resource& operator=(const resource& src) = delete;

            void load_mesh();
    };
}
