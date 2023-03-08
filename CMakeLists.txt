cmake_minimum_required(VERSION 3.25)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(ip_filter VERSION ${PROJECT_VESRION})

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

add_executable(
    ip_filter 
    ip_filter.cpp
)

add_library(ip_filter_class ip_filter_class.cpp)

add_library(md5_hash md5.cpp)

add_executable(
    test_ip_filter_gtest 
    test_ip_filter_gtest.cpp
)

set_target_properties(
    ip_filter
    ip_filter_class
    test_ip_filter_gtest
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    ip_filter_class
    PRIVATE 
    "${CMAKE_BINARY_DIR}"
)

target_include_directories(
    md5_hash
    PRIVATE 
    "${CMAKE_BINARY_DIR}"
)

set_target_properties(
    test_ip_filter_gtest 
    PROPERTIES 
    COMPILE_DEFINITIONS 
    STATIC_LINK
)

target_link_libraries(
    test_ip_filter_gtest 
    gtest 
    gtest_main
    md5_hash
    ip_filter_class
)

target_link_libraries(
    ip_filter 
    PRIVATE 
    ip_filter_class
)

target_link_options(ip_filter PRIVATE -static -static-libgcc -static-libstdc++)

target_link_options(test_ip_filter_gtest PRIVATE -static -static-libgcc -static-libstdc++)

if (MSVC)
    target_compile_options(ip_filter PRIVATE /W4)
    target_compile_options(test_ip_filter_gtest PRIVATE /W4)
    target_compile_options(md5_hash PRIVATE /W4)
    target_compile_options(ip_filter_class PRIVATE /W4)
else ()
    target_compile_options(
        ip_filter 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(
        test_ip_filter_gtest 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(
        md5_hash 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(
        ip_filter_class 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
endif()

install (
    TARGETS 
    ip_filter 
    RUNTIME 
    DESTINATION 
    bin
)

# CPack area
if (WIN32)
    set(CPACK_GENERATOR "ZIP")
else ()
    set(CPACK_GENERATOR "DEB")
endif()
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT https://github.com/4l3x777/homework1)
include(CPack)

# Tests area
enable_testing()

add_test(
    NAME 
    unit_tests_test_ip_filter_gtest 
    COMMAND 
    test_ip_filter_gtest
)
