/**
 * @file bson_deserialize.h
 * @author 李新 
 * @brief 
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common.h"
#include "bson_deserialize.h"

namespace bson_impl {

template<>
bool deserializeValue( bson_iter_t const* iter, int32_t& value ) {
    if(!BSON_ITER_HOLDS_INT32(iter)) {
        return false;
    }
    value = bson_iter_int32(iter);
    return true;
}

template<>
bool deserializeValue( bson_iter_t const* iter, uint32_t& value ) {
    if(!BSON_ITER_HOLDS_INT32(iter)) {
        return false;
    }
    int32_t ival = bson_iter_int32(iter);
    value = *(uint32_t*)&ival;
    return true;
}

template<>
bool deserializeValue( bson_iter_t const* iter, float& value ) {
    if(!BSON_ITER_HOLDS_DOUBLE(iter)) {
        return false;
    }
    value = bson_iter_double(iter);
    return true;
}
template<>
bool deserializeValue( bson_iter_t const* iter, double& value ) {
    if(!BSON_ITER_HOLDS_DOUBLE(iter)) {
        return false;
    }
    value = bson_iter_double(iter);
    return true;
}
template<>
bool deserializeValue( bson_iter_t const* iter, std::string& value ) {
    if(!BSON_ITER_HOLDS_UTF8(iter)) {
        return false;
    }
    uint32_t len;
    auto cstr = bson_iter_utf8(iter, &len);
    value = std::string(cstr, len);
    return true;
}
template<>
bool deserializeValue( bson_iter_t const* iter, char* & value ) {
    if(!BSON_ITER_HOLDS_UTF8(iter)) {
        return false;
    }
    uint32_t len;
    auto cstr = bson_iter_utf8(iter, &len);
    if(value) {
        free(value);
    }
    value = (char*)malloc(len+1);
    strcpy(value, cstr);
    return true;
}


}