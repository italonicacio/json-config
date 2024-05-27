cmake_minimum_required(VERSION 3.22)

project(MyProject CXX)


set(FETCHCONTENT_QUIET OFF CACHE BOOL "Desabilita o modo quiet to FetchContent" FORCE)

include(FetchContent)

FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG        1.9.5
)

FetchContent_MakeAvailable(jsoncpp)


file(GLOB_RECURSE LIBRARY_SOURCES "src/*.cpp")
list(REMOVE_ITEM LIBRARY_SOURCES "src/main.cpp")

add_library (
    JsonConfigCore 
    STATIC
        ${LIBRARY_SOURCES}
)

target_include_directories(
    JsonConfigCore
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    JsonConfigCore
    PUBLIC
        jsoncpp_lib
)

set_target_properties( 
    JsonConfigCore
    PROPERTIES
        ENABLE_EXPORTS ON
        POSITION_INDEPENDENT_CODE ON
)

install (
    TARGETS JsonConfigCore
    DESTINATION ${CMAKE_BINARY_DIR}/lib
)

add_executable(
    jsonconfig 
        "src/main.cpp"
)



target_include_directories(
    jsonconfig 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include

)

target_link_libraries(
    jsonconfig 
    PRIVATE
        JsonConfigCore
)

set_target_properties(jsonconfig PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR enable_tests)
	add_subdirectory(tests/unit-tests)
endif()

