// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef CONFIG_H
#define CONFIG_H


namespace engine
{
    class config
    {
    public:
        static config inst;

    private:
        config() = default;
        ~config() = default;
    };
}
#endif
