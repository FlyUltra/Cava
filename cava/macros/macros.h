//
// Created by PC on 8/3/2025.
//
#include <iostream>
#include "../System.h"

#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H
#define echo(...) hoppy_impl(__VA_ARGS__)

template<typename... Args>
inline void hoppy_impl(const Args&... args) {
    ((std::cout << args << ' '), ...) << '\n';
}



class macros {

};



#endif //ANNOTATIONS_H
