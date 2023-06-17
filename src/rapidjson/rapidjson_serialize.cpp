/**
 * @file rapidjson_serialize.h
 * @author 李新
 * @brief json utility rapidjson 序列化实现
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common.h"
// #include <rapidjson/rapidjson.h>

namespace rapidjson_impl {

template<class T>
bool serializeValue( JsonItem& item, const T& value, JsonAllocator& allocator) {
    return value.serializeToJsonItem(item, allocator);
}
template<>
bool serializeValue( JsonItem& item, const int32_t& value, JsonAllocator& allocator) {
    item.SetInt(value);
    return true;
}
template<>
bool serializeValue( JsonItem& item, const uint32_t& value, JsonAllocator& allocator) {
    item.SetUint(value);
    return true;
}
template<>
bool serializeValue( JsonItem& item, const int64_t& value, JsonAllocator& allocator) {
    item.SetInt64(value);
    return true;
}
template<>
bool serializeValue( JsonItem& item, const uint64_t& value, JsonAllocator& allocator) {
    item.SetUint64(value);
    return true;
}
template<>
bool serializeValue( JsonItem& item, const float& value, JsonAllocator& allocator) {
    item.SetFloat(value);
    return true;
}
template<>
bool serializeValue( JsonItem& item, const double& value, JsonAllocator& allocator) {
    item.SetDouble(value);
    return true;
}
template<>
bool serializeValue( JsonItem& item, char const* const& value, JsonAllocator& allocator) {
    item.SetString(rapidjson::StringRef<char>(value));
    return true;
}

}