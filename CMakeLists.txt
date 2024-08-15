cmake_minimum_required(VERSION 3.21)
project(Findup)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENABLE_TESTING CACHE BOOL OFF "Build Mbed TLS tests." OFF)
set(ENABLE_PROGRAMS CACHE BOOL OFF "Build Mbed TLS programs." OFF)
set(UNSAFE_BUILD CACHE BOOL OFF "Allow unsafe builds. These builds ARE NOT SECURE." OFF)
add_subdirectory(external/mbedtls)

add_executable(findup)
add_subdirectory(src)

target_link_libraries(findup PRIVATE mbedcrypto)
