// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class object_id {
        public:
            static object_id inst;

            int get_object_id();
        private:
            object_id() = default;
            ~object_id() = default;

            int next_id;
    };
}
