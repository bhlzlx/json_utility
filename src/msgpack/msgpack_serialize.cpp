/**
 * @file msgpack_serialize.cpp
 * @author 李新 
 * @brief 
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "msgpack_serialize.h"

namespace msgpack_impl {

    template<>
    bool serializeValue( msgpack_packer* packer, const int& value) {
        msgpack_pack_int32(packer, value);
        return true;
    }
    template<>
    bool serializeValue( msgpack_packer* packer, const uint32_t& value) {
        msgpack_pack_uint32(packer, value);
        return true;
    }
    template<>
    bool serializeValue( msgpack_packer* packer, const float& value) {
        msgpack_pack_float(packer, value);
        return true;
    }
    template<>
    bool serializeValue( msgpack_packer* packer, const double& value) {
        msgpack_pack_double(packer, value);
        return true;
    }
    template<>
    bool serializeValue( msgpack_packer* packer, const std::string& value) {
        msgpack_pack_str_with_body(packer, value.c_str(), value.length());
        return true;
    }
    template<>
    bool serializeValue( msgpack_packer* packer, char const* const& value) {
        msgpack_pack_str_with_body(packer, value, strlen(value));
        return true;
    }

}