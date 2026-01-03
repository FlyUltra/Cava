#include "Integer.h"
#include <string>
#include <charconv>
#include <stdexcept>

std::string Integer::toString() const {
    char buf[16];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), value);
    if (ec == std::errc()) {
        *ptr = '\0';
        return std::string(buf);
    }
    return std::string(buf);
}

std::string Integer::toString(int v) {
    char buf[16];
    if (auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), v); ec == std::errc()) {
        *ptr = '\0';
        return std::string(buf);
    }
    return std::string(buf);
}

int Integer::parseInt(const std::string& s) {
    int result = 0;
    if (auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), result); ec != std::errc() || ptr != s.data() + s.size()) {
        throw std::invalid_argument("Invalid integer: " + s);
    }
    return result;
}

const Integer& Integer::valueOf(int v) {
    static Integer *cache = [] {
        Integer arr[256];
        for (int i = -128; i <= 127; ++i) {
            arr[i + 128] = Integer(i);
        }
        return arr;
    }();
    if (v >= -128 && v <= 127) {
        return cache[v + 128];
    }
    thread_local Integer tmp;
    tmp = v;
    return tmp;
}

