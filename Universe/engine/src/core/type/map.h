// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <stdexcept>
#include <unordered_map>

#include "src/core/def/class_format.h"


namespace engine
{
    template <typename K, typename V>
    class map
    {
        ____________________public____________________
        map() = default;
        map(map&& src) = default;
        map(const map& src) = default;

        bool contains(const K& key) const;
        void add(K&& key, V&& value);
        void add(const K& key, V&& value);
        void add(K&& key, const V& value);
        void add(const K& key, const V& value);

        map& operator=(map&& src) = default;
        map& operator=(const map& src) = default;
        V& operator[](const K& key);
        const V& operator[](const K& key) const;

        ~map() = default;
        ____________________private___________________
        std::unordered_map<K, V> data;
    };


    template <typename K, typename V>
    bool map<K, V>::contains(const K& key) const
    {
        return data.contains(key);
    }

    template <typename K, typename V>
    void map<K, V>::add(K&& key, V&& value)
    {
        data[std::move(key)] = std::move(value);
    }

    template <typename K, typename V>
    void map<K, V>::add(const K& key, V&& value) {
        data[key] = std::move(value);
    }

    template <typename K, typename V>
    void map<K, V>::add(K&& key, const V& value)
    {
        data[std::move(key)] = value;
    }

    template <typename K, typename V>
    void map<K, V>::add(const K& key, const V& value)
    {
        data[key] = value;
    }

    template <typename K, typename V>
    V& map<K, V>::operator[](const K& key)
    {
        if (contains(key))
        {
            return data[key];
        }
        throw std::invalid_argument("Key does not exist");
    }

    template <typename K, typename V>
    const V& map<K, V>::operator[](const K& key) const
    {
        if (contains(key))
        {
            return data[key];
        }
        throw std::invalid_argument("Key does not exist");
    }
}
