// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#ifndef ENGINE_RENDER_CONFIG
#define ENGINE_RENDER_CONFIG

namespace engine::render::config
{
    template <typename t>
    class ref
    {
    public:

        ref(t(* const get) (), void (* const set) (t)) :
            get(get), set(set)
        {}
        ~ref()
        {}

        ref(ref&& src) = default;
        ref(const ref& src) = default;

        ref& operator=(ref&& src) = delete;
        ref& operator=(const ref& src) = delete;

        ref& operator=(t&& src)
        {
            set(src);
            return *this;
        }
        ref& operator=(const t& src)
        {
            set(src);
            return *this;
        }

        operator t()
        {
            return get();
        }
        operator t() const
        {
            return get();
        }

    private:
        t (* const get) ();
        void (* const set) (t);
    };

    class obj
    {
        //
    };
    /*class obj
    {
        obj_def;

        struct
        {
            struct
            {
                string font();
                string shader();
            } engine;

            struct
            {
                string mesh();
                string model();
                string shader();
            } game;
        } dir;
        
        struct
        {
            int32 width();
            int32 height();
            int32 refresh();

            bool windowed();

        } view;
    };*/

   /* class obj
    {
        abstract

        struct
        {
            struct
            {
                string font = u8"res/engine/font/";
                string shader = u8"res/engine/shader/";
            } engine;

            struct
            {
                string mesh = u8"res/game/mesh/";
                string model = u8"res/game/model/";
                string shader = u8"res/game/shader/";
            } game;
        } dir;

        int32 width = 128;
        int32 height = 256;
        int32 refresh = 60;

        bool windowed = true;
    };


    obj& get();*/
}

#endif
