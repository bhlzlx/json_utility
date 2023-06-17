/**
 * @file msgpack_deserialize.cpp
 * @author 李新
 * @brief 
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "msgpack_deserialize.h"

namespace msgpack_impl {

    template<>
    bool deserializeValue(msgpack_object const& obj, int32_t& value) {
        if(
            obj.type == msgpack_object_type::MSGPACK_OBJECT_POSITIVE_INTEGER ||
            obj.type == msgpack_object_type::MSGPACK_OBJECT_NEGATIVE_INTEGER)
        {
            value = (uint32_t)obj.via.i64;
            return true;
        }
        return false; 
    }

    template<>
    bool deserializeValue(msgpack_object const& obj, uint32_t& value) {
        if(
            obj.type == msgpack_object_type::MSGPACK_OBJECT_POSITIVE_INTEGER ||
            obj.type == msgpack_object_type::MSGPACK_OBJECT_NEGATIVE_INTEGER)
        {
            value = (uint32_t)obj.via.u64;
            return true;
        }
        return false; 
    }

    template<>
    bool deserializeValue(msgpack_object const& obj, float& value) {
        if( obj.type == msgpack_object_type::MSGPACK_OBJECT_FLOAT32 ) {
            value = (float)obj.via.f64;
            return true;
        }
        return false; 
    }

    template<>
    bool deserializeValue(msgpack_object const& obj, double& value) {
        if( obj.type == msgpack_object_type::MSGPACK_OBJECT_FLOAT64 ) {
            value = (double)obj.via.f64;
            return true;
        }
        return false; 
    }

    template<>
    bool deserializeValue(msgpack_object const& obj, std::string& value) {
        if( obj.type == msgpack_object_type::MSGPACK_OBJECT_STR ) {
            value.assign(obj.via.str.ptr, obj.via.str.size);
            return true;
        }
        return false; 
    }

}