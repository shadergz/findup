cmake_minimum_required(VERSION 3.21)
project(Findup)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE -Ofast)

set(ENABLE_TESTING OFF CACHE BOOL "Build Mbed TLS tests." FORCE)
set(ENABLE_PROGRAMS OFF CACHE BOOL "Build Mbed TLS programs." FORCE)
set(UNSAFE_BUILD OFF CACHE BOOL "Allow unsafe builds. These builds ARE NOT SECURE." FORCE)
add_subdirectory(external/mbedtls)

add_executable(findup)
add_subdirectory(src)

target_link_libraries(findup PRIVATE mbedcrypto)
