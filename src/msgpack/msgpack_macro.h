#pragma once
/**
 * @file bson_macro.h
 * @author 李新
 * 
 * @brief 
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define MSGPACK_UTILITY_BEGIN public:
#define MSGPACK_UTILITY_END

namespace msgpack_impl {

#include <bitset>

    class KeyFinder {
        msgpack_object_map const*   _m;
        std::bitset<32>             _mask; 
        //
    public:
        KeyFinder( msgpack_object_map const* m ) {
            _m = m;
            _mask.reset();
        }
        msgpack_object const* find(char const* key) {
            for(uint32_t i = 0; i<_m->size; ++i) {
                if(_mask[i]) {
                    continue;
                }
                if(strncmp(_m->ptr[i].key.via.str.ptr, key, _m->ptr[i].key.via.str.size) == 0 ) {
                    _mask.set(i, true);
                    return &_m->ptr[i].val;
                }
            }
            return nullptr;
        }
    };

    class MsgpackSerializer {
    private:
        msgpack_sbuffer         _sbuf;
        msgpack_packer          _packer;
    public:
        MsgpackSerializer()
            : _sbuf{}
            , _packer{}
        {}

        void initialize( int (*write_func)(void* data, const char* buf, size_t len) ) {
            msgpack_packer_init(&_packer, &_sbuf, write_func);
        }

        uint8_t const* buffer() {
            return (uint8_t const*)_sbuf.data;
        }

        size_t size() {
            return _sbuf.size;
        }

        msgpack_packer* packer() {
            return &_packer;
        }

        ~MsgpackSerializer() {
            msgpack_sbuffer_destroy(&_sbuf);
        }
    };

}

#define MSGPACK_SERIALIZE_BEGIN \
void serializeToMsgpack(msgpack_impl::MsgpackSerializer& serializer) const {\
    serializeMsgpackItem(serializer.packer());\
}\
void serializeMsgpackItem( msgpack_packer* packer ) const {\
    uint32_t member_count = 0;\

#define MSGPACK_COUNTER_MEMBER(member) member_count += 1;

#define MSGPACK_INIT_MAP msgpack_pack_map(packer, member_count);

#define MSGPACK_SERIAL_MEMBER(name)\
    msgpack_pack_str_with_body(packer, #name, strlen(#name));\
    msgpack_impl::serializeMember(packer, name);

#define MSGPACK_SERIALIZE_END }


#define MSGPACK_DESERIALIZE_BEGIN \
bool deserializeFromMsgpack(uint8_t const* ptr, size_t len) {\
    msgpack_unpacker unpacker;\
    bool rst = msgpack_unpacker_init(&unpacker, len);\
    if(!rst) {\
        msgpack_unpacker_destroy(&unpacker);\
        assert(false);\
        return false;\
    }\
    if(msgpack_unpacker_buffer_capacity(&unpacker)<len) {\
        rst = msgpack_unpacker_reserve_buffer(&unpacker, len);\
    }\
    memcpy(msgpack_unpacker_buffer(&unpacker), ptr, len);\
    msgpack_unpacker_buffer_consumed(&unpacker, len);\
    msgpack_unpacked unpacked;\
    msgpack_unpacked_init(&unpacked);\
    msgpack_unpack_return ret;\
    if(msgpack_unpacker_next(&unpacker, &unpacked) == MSGPACK_UNPACK_SUCCESS) {\
        rst = deserializeFromMsgpackItem(unpacked.data);\
        msgpack_unpacked_destroy(&unpacked);\
    }\
    msgpack_unpacker_destroy(&unpacker);\
    return rst;\
}\
bool deserializeFromMsgpackItem(msgpack_object const& obj) { \
    if(obj.type != msgpack_object_type::MSGPACK_OBJECT_MAP) { \
        return false;\
    }\
    msgpack_object_map const* m = &obj.via.map;\
    msgpack_impl::KeyFinder finder(m);\


#define MSGPACK_DESERIALIZE_END return true; }

#define MSGPACK_DESERIAL_MEMBER(mem) { \
    msgpack_object const* obj_ptr = finder.find(#mem);\
    if(!obj_ptr) {\
        assert(false && "can not find the key: " #mem);\
        return false;\
    }\
    if(!msgpack_impl::deserializeMember(*obj_ptr, mem)) {\
        assert(false && "error while deserialize the property: " #mem);\
        return false;\
    }\
}

#define MSGPACK_COUNTER_MEMBER_Z(a)                     MSGPACK_COUNTER_MEMBER(a)
#define MSGPACK_COUNTER_MEMBER_1(a)                     MSGPACK_COUNTER_MEMBER_Z(a)
#define MSGPACK_COUNTER_MEMBER_2( a, b)                 MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_1(b) 
#define MSGPACK_COUNTER_MEMBER_3( a, b, c )             MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_2(b,c)
#define MSGPACK_COUNTER_MEMBER_4( a,b,c,d )             MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_3(b,c,d)
#define MSGPACK_COUNTER_MEMBER_5( a,b,c,d,e )           MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_4( b,c,d,e )
#define MSGPACK_COUNTER_MEMBER_6( a,b,c,d,e,f)          MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_5( b,c,d,e,f)
#define MSGPACK_COUNTER_MEMBER_7( a,b,c,d,e,f,g)        MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_6(b,c,d,e,f,g)
#define MSGPACK_COUNTER_MEMBER_8( a,b,c,d,e,f,g,h)      MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_7(b,c,d,e,f,g,h)
#define MSGPACK_COUNTER_MEMBER_9( a,b,c,d,e,f,g,h,i)    MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_8(b,c,d,e,f,g,h,i)
#define MSGPACK_COUNTER_MEMBER_10(a,b,c,d,e,f,g,h,i,j)  MSGPACK_COUNTER_MEMBER_1(a) MSGPACK_COUNTER_MEMBER_9(b,c,d,e,f,g,h,i,j)

#define MSGPACK_SERIAL_MEMBER_Z(a) MSGPACK_SERIAL_MEMBER(a)
#define MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_Z(a)
#define MSGPACK_SERIAL_MEMBER_2( a, b) MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_1(b) 
#define MSGPACK_SERIAL_MEMBER_3( a, b, c ) MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_2(b,c)
#define MSGPACK_SERIAL_MEMBER_4( a,b,c,d ) MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_3(b,c,d)
#define MSGPACK_SERIAL_MEMBER_5( a,b,c,d,e )  MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_4( b,c,d,e )
#define MSGPACK_SERIAL_MEMBER_6( a,b,c,d,e,f)  MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_5( b,c,d,e,f)
#define MSGPACK_SERIAL_MEMBER_7( a,b,c,d,e,f,g)  MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_6(b,c,d,e,f,g)
#define MSGPACK_SERIAL_MEMBER_8( a,b,c,d,e,f,g,h)  MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_7(b,c,d,e,f,g,h)
#define MSGPACK_SERIAL_MEMBER_9( a,b,c,d,e,f,g,h,i)  MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_8(b,c,d,e,f,g,h,i)
#define MSGPACK_SERIAL_MEMBER_10(a,b,c,d,e,f,g,h,i,j)  MSGPACK_SERIAL_MEMBER_1(a) MSGPACK_SERIAL_MEMBER_9(b,c,d,e,f,g,h,i,j)

#define MSGPACK_DESERIAL_MEMBER_Z(a) MSGPACK_DESERIAL_MEMBER(a)
#define MSGPACK_DESERIAL_MEMBER_1( a ) MSGPACK_DESERIAL_MEMBER_Z(a)
#define MSGPACK_DESERIAL_MEMBER_2( a, b) MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_1(b) 
#define MSGPACK_DESERIAL_MEMBER_3( a, b, c ) MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_2(b,c)
#define MSGPACK_DESERIAL_MEMBER_4( a,b,c,d ) MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_3(b,c,d)
#define MSGPACK_DESERIAL_MEMBER_5( a,b,c,d,e )  MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_4( b,c,d,e )
#define MSGPACK_DESERIAL_MEMBER_6( a,b,c,d,e,f)  MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_5( b,c,d,e,f)
#define MSGPACK_DESERIAL_MEMBER_7( a,b,c,d,e,f,g)  MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_6(b,c,d,e,f,g)
#define MSGPACK_DESERIAL_MEMBER_8( a,b,c,d,e,f,g,h)  MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_7(b,c,d,e,f,g,h)
#define MSGPACK_DESERIAL_MEMBER_9( a,b,c,d,e,f,g,h,i)  MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_8(b,c,d,e,f,g,h,i)
#define MSGPACK_DESERIAL_MEMBER_10(a,b,c,d,e,f,g,h,i,j)  MSGPACK_DESERIAL_MEMBER_1(a) MSGPACK_DESERIAL_MEMBER_9(b,c,d,e,f,g,h,i,j)

#define MSGPACK_DEFINE_DESERIALIZE_MEMBERS( ... ) INVOKE_VAR_MACRO(MSGPACK_DESERIAL_MEMBER_,__VA_ARGS__)
#define MSGPACK_DEFINE_SERIALIZE_MEMBERS( ... ) INVOKE_VAR_MACRO(MSGPACK_SERIAL_MEMBER_,__VA_ARGS__)
#define MSGPACK_DEFINE_COUNTER_MEMBERS( ... ) INVOKE_VAR_MACRO(MSGPACK_COUNTER_MEMBER_,__VA_ARGS__)
#define MSGPACK_DEFINE_DESERIALIZE(...) MSGPACK_DESERIALIZE_BEGIN MSGPACK_DEFINE_DESERIALIZE_MEMBERS(__VA_ARGS__) MSGPACK_DESERIALIZE_END
#define MSGPACK_DEFINE_SERIALIZE(...) MSGPACK_SERIALIZE_BEGIN MSGPACK_DEFINE_COUNTER_MEMBERS(__VA_ARGS__)  MSGPACK_INIT_MAP MSGPACK_DEFINE_SERIALIZE_MEMBERS(__VA_ARGS__) MSGPACK_SERIALIZE_END
#define GX_MSGPACK(...) MSGPACK_UTILITY_BEGIN MSGPACK_DEFINE_DESERIALIZE(__VA_ARGS__) MSGPACK_DEFINE_SERIALIZE(__VA_ARGS__)  MSGPACK_UTILITY_END
// #define GX_MSGPACK(...) MSGPACK_UTILITY_BEGIN MSGPACK_DEFINE_SERIALIZE(__VA_ARGS__)  MSGPACK_UTILITY_END