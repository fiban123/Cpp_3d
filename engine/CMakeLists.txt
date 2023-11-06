cmake_minimum_required(VERSION 3.26)
project(3d_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(3d_engine src/main.cpp
        src/util.hpp
        src/settings.hpp
        src/init.hpp
        src/keyboard.hpp
        src/declare.hpp)
include_directories(dependencies/include/ogldev/)
include_directories(dependencies/include/common/)

link_directories(3d_engine dependencies/lib/glew32s.lib)
link_directories(3d_engine dependencies/lib/freeglut_staticd.lib)