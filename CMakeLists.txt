cmake_minimum_required(VERSION 3.10)

project(Plex)

SET ( CMAKE_CXX_FLAGS "-O2")

add_executable(Plex_Seq src/main_seq.cpp)
add_executable(Plex_Par src/main_par.cpp)
target_compile_features(Plex_Seq PRIVATE cxx_std_17)
target_compile_features(Plex_Par PRIVATE cxx_std_17)