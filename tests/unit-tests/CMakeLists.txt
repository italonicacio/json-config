# set(FETCHCONTENT_QUIET OFF CACHE BOOL "Desabilita o modo quiet to FetchContent" FORCE)

# include(FetchContent)

option(INSTALL_DEPS "Install dependencies" OFF)

find_package(GTest QUIET)
message(STATUS "GTest_FOUND: ${GTest_FOUND}")


if(NOT GTest_FOUND)
    message(STATUS "GTest not found, using FetchContent to download it")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )

    FetchContent_MakeAvailable(googletest)

endif()


add_executable(
    json_config_tests 
    run-tests.cpp
    environment-tests.cpp
)

target_link_libraries(json_config_tests PRIVATE JsonConfigCore gtest gtest_main)

target_include_directories(
    json_config_tests 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include 
)

