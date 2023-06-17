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


#include "rapidjson_deserialize.h"

namespace rapidjson_impl {

template<>
bool deserializeValue( JsonItem const& item, int32_t& value ) {
    value = item.GetInt();
    return true;
}
template<>
bool deserializeValue( JsonItem const& item, uint32_t& value ) {
    value = item.GetUint();
    return true;
}
template<>
bool deserializeValue( JsonItem const& item, int64_t& value ) {
    value = item.GetInt64();
    return true;
}
template<>
bool deserializeValue( JsonItem const& item, uint64_t& value ) {
    value = item.GetUint64();
    return true;
}
template<>
bool deserializeValue( JsonItem const& item, float& value ) {
    value = item.GetFloat();
    return true;
}
template<>
bool deserializeValue( JsonItem const& item, double& value ) {
    value = item.GetDouble();
    return true;
}
// template<>
// bool deserializeValue( JsonItem const& item, std::string& value ) {
//     if(!item.IsString()) {
//         return false;
//     }
//     value = item.GetString();
//     return true;
// }
template<>
bool deserializeValue( JsonItem const& item, char* & value ) {
    if(!item.IsString()) {
        return false;
    }
    if(value) {
        delete []value;
    }
    char const* text = item.GetString();
    size_t len = strlen(text);
    value = new char[len+1];
    strncpy(value, text, len);
    // strcpy(value, text);
    return true;
}

}