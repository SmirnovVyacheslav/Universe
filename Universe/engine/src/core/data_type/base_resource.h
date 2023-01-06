// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class base_resource {
    public:
        virtual void load() = 0;
        virtual void initialize() = 0;
    protected:
        base_resource() = default;
        base_resource(base_resource&& src) = default;
        base_resource(const base_resource& src) = default;

        base_resource& operator=(base_resource&& src) = default;
        base_resource& operator=(const base_resource& src) = default;

        virtual ~base_resource() = default;
    };
}
