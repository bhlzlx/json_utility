option(BSON_SUPPORT "support bson" OFF)
option(MSGPACK_SUPPORT "support msgpack" OFF)

add_library(GxJsonUtility)

if( ${RAPIDJSON_INCLUDE} STREQUAL "")
    message(FATAL_ERROR "RAPIDJSON_INCLUDE not specified!")
endif()

target_sources(GxJsonUtility
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GxJsonUtility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GxJsonUtility.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/rapidjson_serialize.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/rapidjson_deserialize.cpp
    $<$<BOOL:${BSON_SUPPORT}>: ${CMAKE_CURRENT_SOURCE_DIR}/bson/bson_serialize.cpp>
    $<$<BOOL:${BSON_SUPPORT}>: ${CMAKE_CURRENT_SOURCE_DIR}/bson/bson_deserialize.cpp>
    $<$<BOOL:${MSGPACK_SUPPORT}>: ${CMAKE_CURRENT_SOURCE_DIR}/msgpack/msgpack_serialize.cpp>
    $<$<BOOL:${MSGPACK_SUPPORT}>: ${CMAKE_CURRENT_SOURCE_DIR}/msgpack/msgpack_deserialize.cpp>
)

if(BSON_SUPPORT)
get_target_property(BSON_BIN_DIR bson_static BINARY_DIR)
get_target_property(BSON_SOURCE_DIR bson_static SOURCE_DIR)
message(${BSON_BIN_DIR})
endif()
if(MSGPACK_SUPPORT)
get_target_property(MSGPACK_SOURCE_DIR msgpackc SOURCE_DIR)
get_target_property(MSGPACK_BIN_DIR msgpackc BINARY_DIR)
message(${BSON_SOURCE_DIR})
endif()

target_include_directories(GxJsonUtility
PUBLIC
    ${RAPIDJSON_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<$<BOOL:${BSON_SUPPORT}>:${BSON_SOURCE_DIR}/src/bson>
    $<$<BOOL:${BSON_SUPPORT}>:${BSON_BIN_DIR}/src/bson>
    # msgpack 的头文件包含相关的工程管理，差点意思！
    $<$<BOOL:${MSGPACK_SUPPORT}>:${MSGPACK_SOURCE_DIR}/include>
    $<$<BOOL:${MSGPACK_SUPPORT}>:${MSGPACK_BIN_DIR}/include/msgpack>
    $<$<BOOL:${MSGPACK_SUPPORT}>:${MSGPACK_BIN_DIR}/include>
)

target_link_libraries(GxJsonUtility
PUBLIC
    $<$<BOOL:${BSON_SUPPORT}>: bson_static>
    $<$<BOOL:${MSGPACK_SUPPORT}>: msgpackc>
)

target_compile_definitions(GxJsonUtility
PRIVATE
    $<$<BOOL:${BSON_SUPPORT}>: BSON_STATIC>
    $<$<BOOL:${BSON_SUPPORT}>: WITH_BSON>
    $<$<BOOL:${MSGPACK_SUPPORT}>: WITH_MSGPACK>
)