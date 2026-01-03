#include "System.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string>
#include <fstream>


namespace System {

    void setColor(Color c) {
        std::cout << "\033[" << static_cast<int>(c) << "m";
    }

    void flush() {
        std::cout.flush();
    }

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
        std::exit(code);
    }

    long long currentTimeMillis() {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    long long nanoTime() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
    }

    std::string readLine() {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    int readInt() {
        std::string line = readLine();
        return std::stoi(line);
    }

    const char* getenv(const std::string& key) {
        return std::getenv(key.c_str());
    }

    std::string getProperty(const std::string& key) {
#ifdef _WIN32
        if (key == "os.name") return "Windows";
#elif __linux__
        if (key == "os.name") return "Linux";
#elif __APPLE__
        if (key == "os.name") return "macOS";
#endif
        return "Unknown";
    }

    void err(const std::string& msg) {
        std::cerr << msg << std::endl;
    }

    void gc() {

    }

}
