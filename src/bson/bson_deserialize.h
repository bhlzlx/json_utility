#pragma once
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

namespace bson_impl {


struct bson_deserialize_entry {
    enum class entry_type {
        bson,
        bson_iter,
    };
    union {
        bson_t const* bson;
        bson_iter_t const* iter;
    };
    entry_type type;

    bson_deserialize_entry( bson_t const* b ) {
        this->bson = b;
        this->type = entry_type::bson;
    }
    bson_deserialize_entry( bson_iter_t const* i ) {
        this->iter = i;
        this->type = entry_type::bson_iter;
    }
    bool get_iter(char const* key, bson_iter_t& child_iter) {
        if(type == entry_type::bson) {
            if(bson_iter_init_find(&child_iter, bson, key)) {
                return true;
            } else {
                return false;
            }
        } else {
            if(bson_iter_recurse(iter, &child_iter)) {
                if(bson_iter_find(&child_iter, key)) {
                    return true;
                }
            }
        }
        return false;
    }
};

template<class T>
bool deserializeValue( bson_iter_t const* iter, T& value) {
    if(!BSON_ITER_HOLDS_DOCUMENT(iter)) {
        return false;
    }
    bson_deserialize_entry entry(iter);
    value.deserializeFromBsonIter(entry);
    return true;
}

template<>
bool deserializeValue( bson_iter_t const* iter, int32_t& value );
template<>
bool deserializeValue( bson_iter_t const* iter, uint32_t& value );
template<>
bool deserializeValue( bson_iter_t const* iter, float& value );
template<>
bool deserializeValue( bson_iter_t const* iter, double& value );
template<>
bool deserializeValue( bson_iter_t const* iter, std::string& value );
template<>
bool deserializeValue( bson_iter_t const* iter, char* & value );
template<class T, size_t SIZE>
bool deserializeValue( bson_iter_t const* iter, T(&value)[SIZE]) {
    if(!BSON_ITER_HOLDS_ARRAY(iter)) {
        return false;
    }
    bson_iter_t child_iter;
    bson_iter_recurse(iter, &child_iter);
    size_t i = 0;
    while(bson_iter_next(&child_iter)) {
        deserializeValue(&child_iter, value[i]);
        ++i;
    }
    return true;
}
template<class T>
bool deserializeValue( bson_iter_t const* iter, std::vector<T>& vec ) {
    if(!BSON_ITER_HOLDS_ARRAY(iter)) {
        return false;
    }
    vec.clear();
    // 目前不能取到array长度，所以这里没办法优化
    // uint32_t raw_len = 0;
    // uint8_t const* raw_ptr = nullptr;
    // bson_iter_array(iter, &raw_ptr);
    bson_iter_t child_iter;
    bson_iter_recurse(iter, &child_iter);
    while(bson_iter_next(&child_iter)) {
        T val;
        deserializeValue(&child_iter, val);
        vec.push_back(std::move(val));
    }
    return true;
}
template<size_t SIZE>
bool deserializeValue( bson_iter_t const* iter, char(&arr)[SIZE] ) {
    if(!BSON_ITER_HOLDS_UTF8(iter)) {
        return false;
    }
    uint32_t len;
    auto cstr = bson_iter_utf8(iter, &len);
    strncpy(arr, cstr, SIZE-1);
    return true;
}
/**
 * @brief 
 *      T is enum type 
 */
template<class T>
BoolE deserializeMember( bson_iter_t const* iter, T& type ) {
    return false;
}
/**
 * @brief 
 *      T is not enum type 
 */
template<class T>
BoolNE deserializeMember( bson_iter_t const* iter, T& type ) {
    return deserializeValue(iter, type);
}

}