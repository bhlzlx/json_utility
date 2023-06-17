#pragma once
/**
 * @file GxJsonUtility.h
 * @author 李新
 * @brief json utility header file
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */


/**
 * @brief 
 * 这里注意，enum也是可以支持的，但是！需要开启RTTI机制，所以暂时就没给加上，有需要再加这个功能。
 */
#pragma once

#include "common.h"

#include "rapidjson/rapidjson_serialize.h"
#include "rapidjson/rapidjson_deserialize.h"
#include "rapidjson/rapidjson_macro.h"
// bson impl
std::string RapidjsonToString(const rapidjson::Document& doc);

template<class T>
std::vector<T> DeserializeJsonVector(char const* text, size_t length) {
    rapidjson::Document doc;
    doc.Parse(text, length);
    std::vector<T> vec;
    if(doc.IsArray()) {
        rapidjson_impl::deserializeValue(doc.GetArray(), vec); 
    }
    return vec;
}

template<class T>
rapidjson::Document SerializeJsonVector(std::vector<T>& vec) {
    rapidjson::Document doc;
    auto rst = rapidjson_impl::serializeValue(doc, vec, doc.GetAllocator());
    return doc;
}

#ifdef WITH_BSON
#include "bson/bson_serialize.h"
#include "bson/bson_deserialize.h"
#include "bson/bson_macro.h"
#else
#define GX_BSON(...)
// bson 用了windows.h，暂时没看为什么，反正非常离谱，有可能是用的了内存分配的东西，离谱。
#endif

#ifdef WITH_MSGPACK
#include "msgpack/msgpack_serialize.h"
#include "msgpack/msgpack_deserialize.h"
#include "msgpack/msgpack_macro.h"
#else
#define GX_MSGPACK(...)
#endif

#ifdef GetObject
    #undef GetObject
#endif