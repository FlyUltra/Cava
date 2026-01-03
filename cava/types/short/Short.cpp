#include "Short.h"
#include <charconv>
#include <stdexcept>
#include <mutex>

std::unique_ptr<Short> Short::cache[Short::CACHE_HIGH - Short::CACHE_LOW + 1] = { nullptr };
static std::once_flag shortCacheFlag;

void Short::initCache() {
    for (int i = CACHE_LOW; i <= CACHE_HIGH; ++i) {
        cache[i - CACHE_LOW] = std::make_unique<Short>(static_cast<short>(i));
    }
}

Short Short::valueOf(short v) {
    std::call_once(shortCacheFlag, Short::initCache);
    if (v >= CACHE_LOW && v <= CACHE_HIGH) {
        return *cache[v - CACHE_LOW];
    }
    return Short(v);
}

Short::Short(int v) {
    if (v < MIN_VALUE || v > MAX_VALUE) {
        throw std::out_of_range("Short out of range: " + std::to_string(v));
    }
    value = static_cast<short>(v);
}

short Short::parseShort(const std::string& s) {
    short result;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), result);
    if (ec != std::errc() || ptr != s.data() + s.size()) {
        throw std::invalid_argument("Invalid short: " + s);
    }
    return result;
}

std::string Short::toString(short v) {
    return std::to_string(v);
}

int Short::compareTo(const Short& other) const {
    return (value < other.value) ? -1 : (value > other.value ? 1 : 0);
}

bool Short::equals(const Short& other) const {
    return value == other.value;
}

bool Short::operator==(const Short& other) const {
    return value == other.value;
}

bool Short::operator!=(const Short& other) const {
    return value != other.value;
}

std::size_t Short::hashCode() const {
    return std::hash<short>()(value);
}

std::ostream& operator<<(std::ostream& os, const Short& s) {
    os << s.value;
    return os;
}
