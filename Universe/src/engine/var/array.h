// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_array.h"


#ifndef ENGINE_ARRAY
#define ENGINE_ARRAY

namespace engine
{
   template <typename T>
   class array
   {
    public:
       array(int32 size = 0);
       array(array&& src) = default;
       array(const array& src) = default;

       int32 size() const;
       void append(T&& item);
       void append(const T& item);
       int32 find_index(const T& item);

       array& operator=(array&& src_ptr) = default;
       array& operator=(const array& src_ptr) = default;
       T& operator[](const int32 index);
       const T& operator[](const int32 index) const;
       T* operator*();
       const T* operator*() const;

       ~array() = default;
   private:
       std::vector<T> data;
   };


   template <typename T>
   array<T>::array(int32 size)
   {
       if (size < 0)
       {
           throw error("Negative array size");
       }
       data.reserve(static_cast<size_t>(size));
   }

   template<typename T>
   int32 array<T>::size() const
   {
       return static_cast<int32>(data.size());
   }

   template <typename T>
   void array<T>::append(T&& item)
   {
       data.push_back(std::move(item));
   }

   template <typename T>
   void array<T>::append(const T& item)
   {
       data.push_back(item);
   }

   template<typename T>
   int32 array<T>::find_index(const T& item)
   {
       for (int32 i = 0; i < size(); ++i)
       {
           if (data[static_cast<size_t>(i)] == item)
           {
               return i;
           }
       }
       throw error("Item does not exist");
   }

   template <typename T>
   T& array<T>::operator[](const int32 index)
   {
       return data[(size() + index % size()) % size()];
   }

   template <typename T>
   const T& array<T>::operator[](const int32 index) const
   {
       return data[(size() + index % size()) % size()];
   }

   template <typename T>
   T* array<T>::operator*()
   {
       return &data.front();
   }

   template <typename T>
   const T* array<T>::operator*() const
   {
       return &data.front();
   }
}

#endif
