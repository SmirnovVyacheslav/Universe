// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_VAR_SOBJ
#define ENGINE_VAR_SOBJ

namespace engine
{
    template <typename t>
    class sobj
    {
    public:
        static t& inst()
        {
            static t obj_inst;
            return obj_inst;
        }
    private:
        sobj()                = default;
        sobj(sobj&& src)      = delete;
        sobj(const sobj& src) = delete;

        sobj& operator=(sobj&& src)      = delete;
        sobj& operator=(const sobj& src) = delete;

        ~sobj() = default;
    };
}

#endif
