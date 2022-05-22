// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef ENGINE_UI_H
#define ENGINE_UI_H


namespace engine
{
    namespace ui
    {
        class engine_ui
        {
        public:
            engine_ui();
            ~engine_ui();

            void add_object();
            void start_render();
        };
    }
}
#endif
