cmake_minimum_required(VERSION 3.21)
target_include_directories(findup PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(findup PRIVATE
    decl.h
    program.cpp
    foreach_dirs.cpp
    filter_storage.cpp
    validate.cpp
    aes.cpp
    aes.h
)