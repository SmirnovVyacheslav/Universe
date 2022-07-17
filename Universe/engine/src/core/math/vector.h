//// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
//#pragma once
//#include <functional>
//#include "src/core/data_type/std.h"
//
//
//namespace engine {
//    template <uint_32 size>
//    struct vector;
//    template <uint_32 size>
//    const vector<size> operator+(const vector<size>& vec_a, const vector<size>& vec_b);
//    template <uint_32 size>
//    const vector<size> operator-(const vector<size>& vec_a, const vector<size>& vec_b);
//    template <uint_32 size>
//    const vector<size> operator+(const vector<size>& vec, const real_32& num);
//    template <uint_32 size>
//    const vector<size> operator-(const vector<size>& vec, const real_32& num);
//    template <uint_32 size>
//    const vector<size> operator*(const vector<size>& vec, const real_32& num);
//    template <uint_32 size>
//    const vector<size> operator/(const vector<size>& vec, const real_32& num);
//    template <uint_32 size>
//    const vector<size> operator+(const real_32& num, const vector<size>& vec);
//    template <uint_32 size>
//    const vector<size> operator-(const real_32& num, const vector<size>& vec);
//    template <uint_32 size>
//    const vector<size> operator*(const real_32& num, const vector<size>& vec);
//    template <uint_32 size>
//    const vector<size> operator/(const real_32& num, const vector<size>& vec);
//    template <uint_32 size>
//    bool operator==(const vector<size>& vec_a, const vector<size>& vec_b);
//    template <uint_32 size>
//    bool operator!=(const vector<size>& vec_a, const vector<size>& vec_b);
//    // Scalar product
//    template <uint_32 size>
//    const real_32 operator*(const vector<size>& vec_a, const vector<size>& vec_b);
//    // Vector product
//    // const vector<static_cast<uint_32>(3)> operator^(const vector<static_cast<uint_32>(3)>& vec_a, const vector<static_cast<uint_32>(3)>& vec_b);
//
//
//    template <uint_32 size>
//    const vector<size> operator+(const vector<size>& vec_a, const vector<size>& vec_b) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = vec_a[i] + vec_b[i];
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator-(const vector<size>& vec_a, const vector<size>& vec_b) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = vec_a[i] - vec_b[i];
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator+(const vector<size>& vec, const real_32& num) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = vec[i] + num;
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator-(const vector<size>& vec, const real_32& num) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = vec[i] - num;
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator*(const vector<size>& vec, const real_32& num) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = vec[i] * num;
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator/(const vector<size>& vec, const real_32& num) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = vec[i] / num;
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator+(const real_32& num, const vector<size>& vec) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = num + vec[i];
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator-(const real_32& num, const vector<size>& vec) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = num - vec[i];
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator*(const real_32& num, const vector<size>& vec) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = num * vec[i];
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    const vector<size> operator/(const real_32& num, const vector<size>& vec) {
//        vector<size> vec_res;
//        for (uint_32 i = 0; i < size; ++i) {
//            vec_res[i] = num / vec[i];
//        }
//        return vec_res;
//    }
//    template <uint_32 size>
//    bool operator==(const vector<size>& vec_a, const vector<size>& vec_b) {
//        for (uint_32 i = 0; i < size; ++i) {
//            if ((vec_a[i] - vec_b[i]) * (vec_a[i] - vec_b[i]) > eps_tmp) {
//                return false;
//            }
//        }
//        return true;
//    }
//    template <uint_32 size>
//    bool operator!=(const vector<size>& vec_a, const vector<size>& vec_b) {
//        return !(vec_a == vec_b);
//    }
//    // Scalar product
//    template <uint_32 size>
//    const real_32 operator*(const vector<size>& vec_a, const vector<size>& vec_b) {
//        real_32 result = 0.0f;
//        for (uint_32 i = 0; i < size; ++i) {
//            result += vec_a[i] * vec_b[i];
//        }
//        return result;
//    }
//    // Vector product
//    //const vector<static_cast<uint_32>(3)> operator^(const vector<static_cast<uint_32>(3)>& vec_a, const vector <static_cast<uint_32>(3)> &vec_b) {
//    //    return vector<static_cast<uint_32>(3)>();
//    //}
//    /*const vector<static_cast<uint_32>(3)> operator^(const vector<static_cast<uint_32>(3)>& vec_a, const vector<static_cast<uint_32>(3)>& vec_b) {
//        vector<static_cast<uint_32>(3)> vec_res;
//        vec_res[0] = vec_a.data[1] * vec_b.data[2] - vec_a.data[2] * vec_b.data[1];
//        vec_res[1] = vec_a.data[2] * vec_b.data[0] - vec_a.data[0] * vec_b.data[2];
//        vec_res[2] = vec_a.data[0] * vec_b.data[1] - vec_a.data[1] * vec_b.data[0];
//        return vec_res;
//    }*/
//}
