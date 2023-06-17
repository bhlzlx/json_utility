#pragma once
/**
 * @file rapidjson_deserialize.h
 * @author 李新
 * @brief json utility rapidjson 反序列化实现
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common.h"

namespace rapidjson_impl {

template<class T>
requires !iteratable<T>
bool deserializeValue( JsonItem const & item, T& value ) {
    return value.deserializeFromJsonItem(item);
}

template<class T>
requires iteratable<T> && char8_string<T>
bool deserializeValue( JsonItem const & item, T& str) {
    if(!item.IsString()) {
        return false;
    }
    auto jstring = item.GetString();
    auto len = strlen(jstring);
    str.resize(len);
    for(size_t i = 0; i<len; ++i) {
        str[i] = jstring[i];
    }
    return true;
}

template<class T>
requires iteratable<T> && !char8_string<T>
bool deserializeValue( JsonItem const & item, T& vec ) {
    if(!item.IsArray()) {
        return false;
    }
    vec.clear();
    auto len = (size_t)item.GetArray().Size();
    vec.reserve(len);
    for (size_t i = 0; i < len; ++i) {
        typename T::value_type val;
        auto& js_arr_item = item.GetArray()[(rapidjson::SizeType)i];
        deserializeValue( js_arr_item, val);
        vec.push_back(std::move(val));
    }
    return true;
}

template<>
bool deserializeValue( JsonItem const& item, int32_t& value );
template<>
bool deserializeValue( JsonItem const& item, uint32_t& value );
template<>
bool deserializeValue( JsonItem const& item, int64_t& value );
template<>
bool deserializeValue( JsonItem const& item, uint64_t& value );
template<>
bool deserializeValue( JsonItem const& item, float& value );
template<>
bool deserializeValue( JsonItem const& item, double& value );
// template<>
// bool deserializeValue( JsonItem const& item, std::string& value );
template<>
bool deserializeValue( JsonItem const& item, char* & value );
template<class T, size_t SIZE>
bool deserializeValue( JsonItem const& item, T(&arr)[SIZE] ) {
    if(!item.IsArray()) {
        return false;
    }
    auto arrItems = item.GetArray();
    auto len = arrItems.Size();
    len = len > SIZE ? SIZE : len;
    for (size_t i = 0; i < len; ++i) {
        deserializeValue(arrItems[i], arr[i]);
    }
    return true;
}
// template<class T>
// bool deserializeValue( JsonItem const& item, std::vector<T>& vec ) {
//     if(!item.IsArray()) {
//         return false;
//     }
//     vec.clear();
//     auto len = (size_t)item.GetArray().Size();
//     vec.reserve(len);
//     for (size_t i = 0; i < len; ++i) {
//         T val;
//         auto& js_arr_item = item.GetArray()[(rapidjson::SizeType)i];
//         deserializeValue( js_arr_item, val);
//         vec.push_back(std::move(val));
//     }
//     return true;
// }
template<size_t SIZE>
bool deserializeValue( JsonItem const& item, char(&arr)[SIZE] ) {
    if (!item.IsString()) {
        return false;
    }
    char const* text = item.GetString();
    strncpy(arr, text, SIZE - 1);
    return true;
}
/**
 * @brief 
 *      T is enum type 
 */
template<class T>
BoolE deserializeMember( JsonItem const& item, T& type ) {
    return false;
}
/**
 * @brief 
 *      T is not enum type 
 */
template<class T>
BoolNE deserializeMember( JsonItem const& item, T& type ) {
    return deserializeValue(item, type);
}

}