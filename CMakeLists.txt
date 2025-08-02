cmake_minimum_required(VERSION 3.10)
project(Cava)

set(CMAKE_CXX_STANDARD 17)


add_executable(Cava
        main.cpp
        cava/System.cpp
        cava/System.h
        cava/types/string/String.cpp
        cava/types/string/String.h
        cava/types/integer/Integer.cpp
        cava/types/integer/Integer.h
        cava/macros/public.h
        cava/macros/private.h
        cava/oop/Interface.cpp
        cava/oop/Interface.h
)