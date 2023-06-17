/**
 * @file msgpack_deserialize.h
 * @author 李新
 * @brief 
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "common.h"

namespace msgpack_impl {

    template<class T>
    bool deserializeValue(msgpack_object const& obj, T& value) {
        return value.deserializeFromMsgpackItem(obj);
    }

    template<size_t SIZE>
    bool deserializeValue(msgpack_object const& obj, char(& str)[SIZE]) {
        if( obj.type == msgpack_object_type::MSGPACK_OBJECT_STR ) {
            strncpy(str, obj.via.str.ptr, min(obj.via.str.size, SIZE));
            return true;
        }
        return false; 
    }

    template<class T, size_t SIZE>
    bool deserializeValue(msgpack_object const& obj, T(& arr)[SIZE]) {
        if(obj.type == msgpack_object_type::MSGPACK_OBJECT_ARRAY) {
            for( uint32_t i = 0; i<obj.via.array.size; ++i) {
                msgpack_object const& obj = obj.via.array.ptr[i];
                deserializeValue(obj, arr[i]);
            }
            return true;
        }
        return false; 
    }

    template<class T>
    bool deserializeValue(msgpack_object const& obj, std::vector<T>& vec) {
        if(obj.type == msgpack_object_type::MSGPACK_OBJECT_ARRAY) {
            vec.clear();
            vec.resize(obj.via.array.size);
            for( uint32_t i = 0; i<obj.via.array.size; ++i) {
                msgpack_object const& obj_item = obj.via.array.ptr[i];
                deserializeValue(obj_item, vec[i]);
            }
            return true;
        }
        return false; 
    }

    template<>
    bool deserializeValue(msgpack_object const& obj, int& value);

    template<>
    bool deserializeValue(msgpack_object const& obj, uint32_t& value);

    template<>
    bool deserializeValue(msgpack_object const& obj, float& value);

    template<>
    bool deserializeValue(msgpack_object const& obj, double& value);

    template<>
    bool deserializeValue(msgpack_object const& obj, std::string& value);

    /**
     * @brief 
     *      T is enum type 
     */
    template<class T>
    BoolE deserializeMember(msgpack_object const& obj, T& value ) {
        return false;
    }
    /**
     * @brief 
     *      T is not enum type 
     */
    template<class T>
    BoolNE deserializeMember(msgpack_object const& obj, T& value ) {
        return deserializeValue(obj, value);
    }

}