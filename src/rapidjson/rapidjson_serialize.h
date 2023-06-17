#pragma once
/**
 * @file rapidjson_serialize.h
 * @author 李新
 * @brief json utility rapidjson 序列化实现
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 * @edit 现在需要C++20 concepts支持
 */
#include <type_traits>
#include <concepts>

namespace rapidjson_impl {

template<class T> // 默认匹配
requires !iteratable<T>
bool serializeValue( JsonItem& item, T const& value, JsonAllocator& allocator) {
    return value.serializeToJsonItem(item, allocator);
}

template<class T> // 字符串匹配（string, u8string, string_view, u8string_view）
requires iteratable<T> && char8_string<T>
bool serializeValue(JsonItem& item,  const T& str, JsonAllocator& allocator) {
    auto ch_ptr = &str[0];
    item.SetString(rapidjson::StringRef<char>((char const*)ch_ptr, str.length()));
    return true;
}

template<class T> // vector, list ...
requires iteratable<T> && !char8_string<T>
bool serializeValue( JsonItem& item, T const& t, JsonAllocator& allocator) {
    item.SetArray();
    auto jarr = item.GetArray();
    for(auto iter = t.begin(); iter !=t.end(); ++iter) {
        rapidjson::Value it;
        auto const& val = *iter;
        serializeValue(it, val, allocator);
        jarr.PushBack(it, allocator);
    }
    return true;
}

template<>
bool serializeValue( JsonItem& item, const int32_t& value, JsonAllocator& allocator);
template<>
bool serializeValue( JsonItem& item, const uint32_t& value, JsonAllocator& allocator);
template<>
bool serializeValue( JsonItem& item, const int64_t& value, JsonAllocator& allocator);
template<>
bool serializeValue( JsonItem& item, const uint64_t& value, JsonAllocator& allocator);
template<>
bool serializeValue( JsonItem& item, const float& value, JsonAllocator& allocator);
template<>
bool serializeValue( JsonItem& item, const double& value, JsonAllocator& allocator);
template<>
bool serializeValue( JsonItem& item, const std::string& value, JsonAllocator& allocator);
template<>
bool serializeValue( JsonItem& item, char const* const& value, JsonAllocator& allocator);
template<class T, size_t SIZE>
bool serializeValue( JsonItem& item, const T(&arr)[SIZE], JsonAllocator& allocator) {
    item.SetArray();
    auto jarr = item.GetArray();
    for( const auto& val: arr) {
        rapidjson::Value it;
        serializeValue(it, val, allocator);
        jarr.PushBack(it, allocator);
    }
    return true;
}
// template<class T>
// bool serializeValue( JsonItem& item, const std::vector<T>& vec, JsonAllocator& allocator) {
//     item.SetArray();
//     auto jarr = item.GetArray();
//     for(const auto& val: vec) {
//         rapidjson::Value it;
//         serializeValue(it, val, allocator);
//         jarr.PushBack(it, allocator);
//     }
//     return true;
// }
template<size_t SIZE>
bool serializeValue( JsonItem& item, const char(&arr)[SIZE], JsonAllocator& allocator) {
    item.SetString(rapidjson::StringRef<char>(&arr[0]));
    return true;
}
/**
 * @brief 
 *      T is enum type 
 */
template<class T>
BoolE serializeMember(JsonItem& item, const T& type, JsonAllocator& allocator) {
    return false;
}
/**
 * @brief 
 *      T is not enum type 
 */
template<class T>
BoolNE serializeMember( JsonItem& item, const T& type, JsonAllocator& allocator) {
    return serializeValue(item, type, allocator);
}

}