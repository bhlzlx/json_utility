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

namespace bson_impl {
    struct BsonSerializeRst {
        bson_t* _bson; 
        BsonSerializeRst()
            : _bson(bson_new())
        {
        }
        uint8_t const*  buffer() const{
            return (uint8_t const*)bson_get_data(_bson);
        }
        uint32_t size() const {
            return _bson->len;
        }
        bson_t* bson() {
            return _bson;
        }
        ~BsonSerializeRst() {
            if(_bson) {
                bson_destroy(_bson);
                _bson = nullptr;
            }
        }
    };
}

#define BSON_UTILITY_BEGIN public:
#define BSON_UTILITY_END

#define BSON_SERIALIZE_BEGIN \
void serializeToBSON( bson_impl::BsonSerializeRst& rst ) {\
    serializeToBsonItem(rst.bson());\
}\
bool serializeToBsonItem(bson_t* bson) const {

#define BSON_SERIALIZE_END return true; }

#define BSON_SERIAL_MEMBER(mem) bson_impl::serializeMember(bson, #mem, mem);

#define BSON_DESERIALIZE_BEGIN \
bool deserializeFromBson( uint8_t const* ptr, size_t len) {\
    bson_t bson;\
    if(!bson_init_static(&bson, ptr, len)) {\
        return false;\
    }\
    bson_impl::bson_deserialize_entry entry(&bson);\
    return deserializeFromBsonIter(entry);\
}\
bool deserializeFromBsonIter( bson_impl::bson_deserialize_entry& entry ) {\

#define BSON_DESERIALIZE_END return true; }

#define BSON_DESERIAL_MEMBER(mem) { \
    auto name = #mem;\
    bson_iter_t iter = {};\
    if(entry.get_iter(name,iter)) {\
        bson_impl::deserializeMember(&iter, mem); \
    }\
}

#define BSON_SERIAL_MEMBER_Z(a) BSON_SERIAL_MEMBER(a)
#define BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_Z(a)
#define BSON_SERIAL_MEMBER_2( a, b) BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_1(b) 
#define BSON_SERIAL_MEMBER_3( a, b, c ) BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_2(b,c)
#define BSON_SERIAL_MEMBER_4( a,b,c,d ) BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_3(b,c,d)
#define BSON_SERIAL_MEMBER_5( a,b,c,d,e )  BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_4( b,c,d,e )
#define BSON_SERIAL_MEMBER_6( a,b,c,d,e,f)  BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_5( b,c,d,e,f)
#define BSON_SERIAL_MEMBER_7( a,b,c,d,e,f,g)  BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_6(b,c,d,e,f,g)
#define BSON_SERIAL_MEMBER_8( a,b,c,d,e,f,g,h)  BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_7(b,c,d,e,f,g,h)
#define BSON_SERIAL_MEMBER_9( a,b,c,d,e,f,g,h,i)  BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_8(b,c,d,e,f,g,h,i)
#define BSON_SERIAL_MEMBER_10(a,b,c,d,e,f,g,h,i,j)  BSON_SERIAL_MEMBER_1(a) BSON_SERIAL_MEMBER_9(b,c,d,e,f,g,h,i,j)

#define BSON_DESERIAL_MEMBER_Z(a) BSON_DESERIAL_MEMBER(a)
#define BSON_DESERIAL_MEMBER_1( a ) BSON_DESERIAL_MEMBER_Z(a)
#define BSON_DESERIAL_MEMBER_2( a, b) BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_1(b) 
#define BSON_DESERIAL_MEMBER_3( a, b, c ) BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_2(b,c)
#define BSON_DESERIAL_MEMBER_4( a,b,c,d ) BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_3(b,c,d)
#define BSON_DESERIAL_MEMBER_5( a,b,c,d,e )  BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_4( b,c,d,e )
#define BSON_DESERIAL_MEMBER_6( a,b,c,d,e,f)  BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_5( b,c,d,e,f)
#define BSON_DESERIAL_MEMBER_7( a,b,c,d,e,f,g)  BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_6(b,c,d,e,f,g)
#define BSON_DESERIAL_MEMBER_8( a,b,c,d,e,f,g,h)  BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_7(b,c,d,e,f,g,h)
#define BSON_DESERIAL_MEMBER_9( a,b,c,d,e,f,g,h,i)  BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_8(b,c,d,e,f,g,h,i)
#define BSON_DESERIAL_MEMBER_10(a,b,c,d,e,f,g,h,i,j)  BSON_DESERIAL_MEMBER_1(a) BSON_DESERIAL_MEMBER_9(b,c,d,e,f,g,h,i,j)

#define BSON_DEFINE_DESERIALIZE_MEMBERS( ... ) INVOKE_VAR_MACRO(BSON_DESERIAL_MEMBER_,__VA_ARGS__)
#define BSON_DEFINE_SERIALIZE_MEMBERS( ... ) INVOKE_VAR_MACRO(BSON_SERIAL_MEMBER_,__VA_ARGS__)
#define BSON_DEFINE_DESERIALIZE(...) BSON_DESERIALIZE_BEGIN BSON_DEFINE_DESERIALIZE_MEMBERS(__VA_ARGS__) BSON_DESERIALIZE_END
#define BSON_DEFINE_SERIALIZE(...) BSON_SERIALIZE_BEGIN BSON_DEFINE_SERIALIZE_MEMBERS(__VA_ARGS__) BSON_SERIALIZE_END
#define GX_BSON(...) BSON_UTILITY_BEGIN BSON_DEFINE_DESERIALIZE(__VA_ARGS__) BSON_DEFINE_SERIALIZE(__VA_ARGS__)  BSON_UTILITY_END