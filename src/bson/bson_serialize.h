#pragma once

#include "common.h"
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

namespace bson_impl {

template<class T>
bool serializeValue( bson_t* bson, char const* key, const T& value) {
    bson_t child;
    bson_append_document_begin(bson, key, -1, &child);
    value.serializeToBsonItem(&child);
    bson_append_document_end(bson, &child);
    return true;
}
template<>
bool serializeValue( bson_t* bson, char const* key, const int& value);
template<>
bool serializeValue( bson_t* bson, char const* key, const uint32_t& value);
template<>
bool serializeValue( bson_t* bson, char const* key, const float& value);
template<>
bool serializeValue( bson_t* bson, char const* key, const double& value);
template<>
bool serializeValue( bson_t* bson, char const* key, const std::string& value);
template<>
bool serializeValue( bson_t* bson, char const* key, char const* const& value);
template<class T, size_t SIZE>
bool serializeValue( bson_t* bson, char const* key, const T(& arr)[SIZE]) {
    bson_t bson_arr;
    bson_append_array_begin(bson, key, -1, &bson_arr);
    char keybuffer[16];
    for( size_t i = 0; i<SIZE; ++i) {
        sprintf(keybuffer, "%zu", i);
        serializeValue(&bson_arr,keybuffer, arr[i]);
    }
    bson_append_array_end(bson, &bson_arr);
    return true;
}
template<class T>
bool serializeValue( bson_t* bson, char const* key, const std::vector<T>& vec) {
    bson_t arr;
    bson_append_array_begin(bson, key, -1, &arr);
    char keybuffer[16];
    for( size_t i = 0; i<vec.size(); ++i) {
        sprintf(keybuffer, "%zu", i);
        serializeValue(&arr,keybuffer, vec[i]);
    }
    bson_append_array_end(bson, &arr);
    return true;
}
template<size_t SIZE>
bool serializeValue( bson_t* bson, char const* key, const char(&arr)[SIZE]) {
    bson_append_utf8(bson, key, -1, &arr[0], strlen(arr));
    return true;
}
/**
 * @brief 
 *      T is enum type 
 */
template<class T>
BoolE serializeMember( bson_t* bson, char const* key, const T& value) {
    return false;
}
/**
 * @brief 
 *      T is not enum type 
 */
template<class T>
BoolNE serializeMember( bson_t* bson, char const* key, const T& value) {
    return serializeValue(bson, key, value);
}

}