#include "Long.h"
#include <charconv>
#include <stdexcept>
#include <mutex>

std::unique_ptr<Long> Long::cache[Long::CACHE_HIGH - Long::CACHE_LOW + 1] = { nullptr };
static std::once_flag longCacheFlag;

void Long::initCache() {
    for (long long i = CACHE_LOW; i <= CACHE_HIGH; ++i) {
        cache[i - CACHE_LOW] = std::make_unique<Long>(i);
    }
}

Long Long::valueOf(long long v) {
    std::call_once(longCacheFlag, Long::initCache);
    if (v >= CACHE_LOW && v <= CACHE_HIGH) {
        return *cache[v - CACHE_LOW];
    }
    return Long(v);
}

Long::Long(long double v) {
    if (v < static_cast<long double>(MIN_VALUE) || v > static_cast<long double>(MAX_VALUE)) {
        throw std::out_of_range("Long out of range: " + std::to_string(v));
    }
    value = static_cast<long long>(v);
}

long long Long::parseLong(const std::string& s) {
    long long result;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), result);
    if (ec != std::errc() || ptr != s.data() + s.size()) {
        throw std::invalid_argument("Invalid long: " + s);
    }
    return result;
}

std::string Long::toString(long long v) {
    return std::to_string(v);
}

int Long::compareTo(const Long& other) const {
    return (value < other.value) ? -1 : (value > other.value ? 1 : 0);
}

bool Long::equals(const Long& other) const {
    return value == other.value;
}

bool Long::operator==(const Long& other) const {
    return value == other.value;
}

bool Long::operator!=(const Long& other) const {
    return value != other.value;
}

std::size_t Long::hashCode() const {
    return std::hash<long long>()(value);
}

std::ostream& operator<<(std::ostream& os, const Long& l) {
    os << l.value;
    return os;
}
