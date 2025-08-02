#include "Integer.h"
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <mutex>

bool Integer::cacheInitialized = false;
Integer* Integer::cache[Integer::CACHE_HIGH - Integer::CACHE_LOW + 1] = { nullptr };

static std::once_flag cacheFlag;

void Integer::initCache() {
    for (int i = CACHE_LOW; i <= CACHE_HIGH; ++i) {
        cache[i - CACHE_LOW] = new Integer(i);
    }
    cacheInitialized = true;
}

Integer Integer::valueOf(int v) {
    std::call_once(cacheFlag, []() { Integer::initCache(); });
    if (v >= CACHE_LOW && v <= CACHE_HIGH) {
        return *cache[v - CACHE_LOW];
    }
    return Integer(v);
}

int Integer::parseInt(const std::string& s) {
    try {
        size_t idx = 0;
        long l = std::stol(s, &idx, 10);
        if (idx != s.size()) throw std::invalid_argument("Invalid integer: " + s);
        if (l < MIN_VALUE || l > MAX_VALUE) throw std::out_of_range("Integer out of range: " + s);
        return static_cast<int>(l);
    } catch (const std::exception& e) {
        throw;
    }
}

std::string Integer::toStringStatic(int v) {
    return std::to_string(v);
}

int Integer::compareTo(const Integer& other) const {
    if (value < other.value) return -1;
    if (value > other.value) return 1;
    return 0;
}

bool Integer::equals(const Integer& other) const {
    return value == other.value;
}

std::size_t Integer::hashCode() const {
    return std::hash<int>()(value);
}

int Integer::max(int a, int b) {
    return a >= b ? a : b;
}

int Integer::min(int a, int b) {
    return a <= b ? a : b;
}
