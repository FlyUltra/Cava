#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#pragma once

namespace System {

    enum class Color {
        Red = 31, Green = 32, Yellow = 33, Blue = 34, Default = 39
    };

    void setColor(Color c);
    void flush();

    void print(const std::string& message);
    void println(const std::string& message);
    void println();

    [[noreturn]] void exit(int code);

    long long currentTimeMillis();
    long long nanoTime();

    std::string readLine();
    int readInt();

    const char* getenv(const std::string& key);
    std::string getProperty(const std::string& key);

    void err(const std::string& msg);
    void gc();

    template<typename T>
    void print(const T& value) {
        std::cout << value;
    }

    template<typename T>
    void println(const T& value) {
        std::cout << value << std::endl;
    }

    template<typename T, typename... Args>
    void print(const T& first, const Args&... rest) {
        std::cout << first;
        (std::cout << ... << rest);
    }

    template<typename T, typename... Args>
    void println(const T& first, const Args&... rest) {
        print(first, rest...);
        std::cout << std::endl;
    }

    template<typename T>
    void err(const T& val) {
        std::cerr << val << std::endl;
    }

}
