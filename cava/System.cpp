#include "System.h"
#include <iostream>
#include <cstdlib>
#include <sstream>


namespace System {

    void print(const std::string& message) {
        std::cout << message;
    }

    void println(const std::string& message) {
        std::cout << message << std::endl;
    }

    void println() {
        std::cout << std::endl;
    }

    [[noreturn]] void exit(int code) {
        std::flush(std::cout);
        std::exit(code);
    }

}
