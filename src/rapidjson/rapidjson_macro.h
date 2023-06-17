#pragma once
/**
 * @file rapidjson_macro.h
 * @author 李新
 * @brief json utility rapidjson 宏实现
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define JSON_UTILITY_BEGIN public:
#define JSON_UTILITY_END

#define JSON_SERIALIZE_BEGIN \
rapidjson::Document serializeToJSON() {\
    rapidjson::Document doc;\
    auto allocator = doc.GetAllocator();\
    serializeToJsonItem(doc, allocator);\
    return doc;\
}\
bool serializeToJsonItem( JsonItem& item, JsonAllocator& allocator ) const {\
    item.SetObject(); \
    auto obj = item.GetObject();\

#define JSON_SERIALIZE_END return true; }

#define JSON_SERIAL_MEMBER(mem) { \
    JsonItem child;\
    if(rapidjson_impl::serializeMember(child, mem, allocator)) {\
        item.AddMember(#mem, child, allocator);\
    }\
}

#define JSON_DESERIALIZE_BEGIN \
bool deserializeFromJSON(char const* text) {\
    rapidjson::Document doc;\
    doc.Parse(text);\
    if(doc.HasParseError()) {\
        return false;\
    }\
    return deserializeFromJsonItem(doc);\
}\
bool deserializeFromJsonItem( JsonItem const& item ) {\
    if(!item.IsObject()) {\
        return false;\
    }\
    auto obj = item.GetObject();\

#define JSON_DESERIALIZE_END return true; }

#define JSON_DESERIAL_MEMBER(mem) { \
    auto name = #mem;\
	auto iter = obj.FindMember(name); \
	if (iter != obj.end()) { \
		rapidjson_impl::deserializeMember(iter->value, this->mem); \
	}\
}

#define JSON_SERIAL_MEMBER_Z(a) JSON_SERIAL_MEMBER(a)
#define JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_Z(a)
#define JSON_SERIAL_MEMBER_2(a, b) JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_1(b) 
#define JSON_SERIAL_MEMBER_3(a, b, c) JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_2(b,c)
#define JSON_SERIAL_MEMBER_4(a,b,c,d) JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_3(b,c,d)
#define JSON_SERIAL_MEMBER_5(a,b,c,d,e)  JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_4( b,c,d,e)
#define JSON_SERIAL_MEMBER_6(a,b,c,d,e,f)  JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_5(b,c,d,e,f)
#define JSON_SERIAL_MEMBER_7(a,b,c,d,e,f,g)  JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_6(b,c,d,e,f,g)
#define JSON_SERIAL_MEMBER_8(a,b,c,d,e,f,g,h)  JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_7(b,c,d,e,f,g,h)
#define JSON_SERIAL_MEMBER_9(a,b,c,d,e,f,g,h,i)  JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_8(b,c,d,e,f,g,h,i)
#define JSON_SERIAL_MEMBER_10(a,b,c,d,e,f,g,h,i,j)  JSON_SERIAL_MEMBER_1(a) JSON_SERIAL_MEMBER_9(b,c,d,e,f,g,h,i,j)

#define JSON_DESERIAL_MEMBER_Z(a) JSON_DESERIAL_MEMBER(a)
#define JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_Z(a)
#define JSON_DESERIAL_MEMBER_2(a, b) JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_1(b) 
#define JSON_DESERIAL_MEMBER_3(a, b, c) JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_2(b,c)
#define JSON_DESERIAL_MEMBER_4(a,b,c,d) JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_3(b,c,d)
#define JSON_DESERIAL_MEMBER_5(a,b,c,d,e)  JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_4(b,c,d,e)
#define JSON_DESERIAL_MEMBER_6(a,b,c,d,e,f)  JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_5(b,c,d,e,f)
#define JSON_DESERIAL_MEMBER_7(a,b,c,d,e,f,g)  JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_6(b,c,d,e,f,g)
#define JSON_DESERIAL_MEMBER_8(a,b,c,d,e,f,g,h)  JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_7(b,c,d,e,f,g,h)
#define JSON_DESERIAL_MEMBER_9(a,b,c,d,e,f,g,h,i)  JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_8(b,c,d,e,f,g,h,i)
#define JSON_DESERIAL_MEMBER_10(a,b,c,d,e,f,g,h,i,j)  JSON_DESERIAL_MEMBER_1(a) JSON_DESERIAL_MEMBER_9(b,c,d,e,f,g,h,i,j)

#define JSON_DEFINE_DESERIALIZE_MEMBERS( ... ) INVOKE_VAR_MACRO(JSON_DESERIAL_MEMBER_,__VA_ARGS__)
#define JSON_DEFINE_SERIALIZE_MEMBERS( ... ) INVOKE_VAR_MACRO(JSON_SERIAL_MEMBER_,__VA_ARGS__)
#define JSON_DEFINE_DESERIALIZE(...) JSON_DESERIALIZE_BEGIN JSON_DEFINE_DESERIALIZE_MEMBERS(__VA_ARGS__) JSON_DESERIALIZE_END
#define JSON_DEFINE_SERIALIZE(...) JSON_SERIALIZE_BEGIN JSON_DEFINE_SERIALIZE_MEMBERS(__VA_ARGS__) JSON_SERIALIZE_END
#define GX_JSON(...) JSON_UTILITY_BEGIN  JSON_DEFINE_DESERIALIZE(__VA_ARGS__)  JSON_DEFINE_SERIALIZE(__VA_ARGS__)  JSON_UTILITY_END