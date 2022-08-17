// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    namespace ui {
        class engine_ui {
            public:
                engine_ui();
                ~engine_ui();

                void load();
                void add_object();
                void render();
        };
    }
}
