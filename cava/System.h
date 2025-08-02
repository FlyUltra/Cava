#pragma once
#include <string>
#include <iostream>
#include <sstream>

namespace System {

    void print(const std::string& message);
    void println(const std::string& message);
    void println();

    [[noreturn]] void exit(int code);

    template<typename T>
    void print(const T& value) {
        std::ostringstream oss;
        oss << value;
        std::cout << oss.str();
    }

    template<typename T>
    void println(const T& value) {
        std::ostringstream oss;
        oss << value;
        std::cout << oss.str() << std::endl;
    }

}