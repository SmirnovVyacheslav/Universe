//// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
//
//#ifndef ENGINE_LIB_DT_COMP_ARRAY
//#define ENGINE_LIB_DT_COMP_ARRAY
//
//#include <vector>
//
//#include "engine/lib/dt/base.h"
//
//#include "engine/var/error.h"
//
//
//namespace engine::lib::dt::comp
//{
//    template <typename t>
//    class array
//    {
//    public:
//        array(int32 size = 0)
//        {
//            if (size < 0)
//            {
//                throw error("Negative array size");
//            }
//            data.reserve(static_cast<size_t>(size));
//        }
//        array(array&& src) = default;
//        array(const array& src) = default;
//
//        int32 size() const;
//        void append(T&& item);
//        void append(const T& item);
//        int32 find_index(const T& item);
//
//        array& operator=(array&& src_ptr) = default;
//        array& operator=(const array& src_ptr) = default;
//        T& operator[](const int32 index);
//        const T& operator[](const int32 index) const;
//        T* operator*();
//        const T* operator*() const;
//
//        ~array() = default;
//    private:
//        std::vector<T> data;
//    };
//}
//
//#endif
