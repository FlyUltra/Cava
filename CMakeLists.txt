cmake_minimum_required(VERSION 3.10)
project(Cava LANGUAGES CXX)

# Globální nastavení standardu (platí pro všechny targety)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Optimalizace pro Release
string(APPEND CMAKE_CXX_FLAGS_RELEASE " -O3 -march=native -flto")
string(APPEND CMAKE_EXE_LINKER_FLAGS " -static")

# TADY BYL PROBLÉM - smazal jsem ten první add_executable(Cava main.cpp)
# Definujeme target Cava se všemi soubory najednou
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
        cava/types/short/Short.cpp
        cava/types/short/Short.h
        cava/types/long/Long.cpp
        cava/types/long/Long.h
        cava/types/byte/Byte.cpp
        cava/types/byte/Byte.h
        cava/types/boolean/Boolean.cpp
        cava/types/boolean/Boolean.h
        cava/types/character/Character.cpp
        cava/types/character/Character.h
        cava/types/double/Double.cpp
        cava/types/double/Double.h
        cava/benchmark/Bench.cpp
        cava/benchmark/Bench.h
        cava/macros/macros.cpp
        cava/macros/macros.h
        cava/types/object/Object.cpp
        cava/types/object/Object.h
        cava/collections/HashMap.cpp
        cava/collections/HashMap.h
)

# Nastavení varování (Warningy jsou super, v C++ tě zachrání)
target_compile_options(Cava PRIVATE
        -Wall -Wextra -Wshadow -Wconversion -Wpedantic
)

# LTO / IPO optimalizace (pokud je podporována)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_output)
if(ipo_supported)
    set_target_properties(Cava PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()