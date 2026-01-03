#include "Byte.h"
#include <charconv>
#include <stdexcept>
#include <mutex>

std::unique_ptr<Byte> Byte::cache[Byte::CACHE_HIGH - Byte::CACHE_LOW + 1] = { nullptr };
static std::once_flag byteCacheFlag;

void Byte::initCache() {
    for (int i = CACHE_LOW; i <= CACHE_HIGH; ++i) {
        cache[i - CACHE_LOW] = std::make_unique<Byte>(static_cast<int8_t>(i));
    }
}

Byte Byte::valueOf(int8_t v) {
    std::call_once(byteCacheFlag, Byte::initCache);
    if (v >= CACHE_LOW && v <= CACHE_HIGH) {
        return *cache[v - CACHE_LOW];
    }
    return Byte(v);
}

Byte::Byte(int v) {
    if (v < MIN_VALUE || v > MAX_VALUE) {
        throw std::out_of_range("Byte out of range: " + std::to_string(v));
    }
    value = static_cast<int8_t>(v);
}

int8_t Byte::parseByte(const std::string& s) {
    int result;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), result);
    if (ec != std::errc() || ptr != s.data() + s.size() || result < MIN_VALUE || result > MAX_VALUE) {
        throw std::invalid_argument("Invalid byte: " + s);
    }
    return static_cast<int8_t>(result);
}

std::string Byte::toString(int8_t v) {
    return std::to_string(static_cast<int>(v));
}

int Byte::compareTo(const Byte& other) const {
    return (value < other.value) ? -1 : (value > other.value ? 1 : 0);
}

bool Byte::equals(const Byte& other) const {
    return value == other.value;
}

bool Byte::operator==(const Byte& other) const {
    return value == other.value;
}

bool Byte::operator!=(const Byte& other) const {
    return value != other.value;
}

std::size_t Byte::hashCode() const {
    return std::hash<int8_t>()(value);
}

std::ostream& operator<<(std::ostream& os, const Byte& b) {
    os << static_cast<int>(b.value);
    return os;
}
