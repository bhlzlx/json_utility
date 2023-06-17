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
namespace msgpack_impl {

    template<class T>
    bool serializeValue(msgpack_packer* packer, const T& value) {
        value.serializeMsgpackItem(packer);
        return true;
    }
    template<>
    bool serializeValue( msgpack_packer* packer, const int& value);
    template<>
    bool serializeValue( msgpack_packer* packer, const uint32_t& value);
    template<>
    bool serializeValue( msgpack_packer* packer, const float& value);
    template<>
    bool serializeValue( msgpack_packer* packer, const double& value);
    template<>
    bool serializeValue( msgpack_packer* packer, const std::string& value);
    template<>
    bool serializeValue( msgpack_packer* packer, char const* const& value);
    template<class T, size_t SIZE>
    bool serializeValue( msgpack_packer* packer, const T(& arr)[SIZE]) {
        msgpack_pack_array(packer, SIZE);
        for( size_t i = 0; i<SIZE; ++i) {
            serializeValue(packer, arr[i]);
        }
        return true;
    }
    template<class T>
    bool serializeValue( msgpack_packer* packer, const std::vector<T>& vec) {
        msgpack_pack_array(packer, vec.size());
        for( size_t i = 0; i<vec.size(); ++i) {
            serializeValue(packer, vec[i]);
        }
        return true;
    }
    template<size_t SIZE>
    bool serializeValue( msgpack_packer* packer, const char(&arr)[SIZE]) {
        msgpack_pack_str_with_body(packer, arr, strlen(arr));
        return true;
    }
    /**
     * @brief 
     *      T is enum type 
     */
    template<class T>
    BoolE serializeMember( msgpack_packer* packer, const T& value) {
        return false;
    }
    /**
     * @brief 
     *      T is not enum type 
     */
    template<class T>
    BoolNE serializeMember( msgpack_packer* packer, const T& value) {
        serializeValue(packer, value);
        return true;
    }

}