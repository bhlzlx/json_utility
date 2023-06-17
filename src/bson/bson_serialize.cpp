/**
 * @file bson_serialize.h
 * @author 李新
 * @brief 
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "bson_serialize.h"

namespace bson_impl {

template<>
bool serializeValue( bson_t* bson, char const* key, const int& value) {
    bson_append_int32(bson, key, -1, value);
    return true;
}
template<>
bool serializeValue( bson_t* bson, char const* key, const uint32_t& value) {
    bson_append_int32(bson, key, -1, (int32_t)value);
    return true;
}
template<>
bool serializeValue( bson_t* bson, char const* key, const float& value) {
    bson_append_double(bson, key, -1, (double)value);
    return true;
}
template<>
bool serializeValue( bson_t* bson, char const* key, const double& value) {
    bson_append_double(bson, key, -1, value);
    return true;
}
template<>
bool serializeValue( bson_t* bson, char const* key, const std::string& value) {
    bson_append_utf8(bson, key, -1, value.c_str(), value.length());
    return true;
}
template<>
bool serializeValue( bson_t* bson, char const* key, char const* const& value) {
    bson_append_utf8(bson, key, -1, value, -1);
    return true;
}

}