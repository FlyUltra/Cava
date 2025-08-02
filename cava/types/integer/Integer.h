#pragma once

#include <string>
#include <cstdint>
#include <ostream>

class Integer {
    int32_t value;
public:
    static constexpr int MIN_VALUE = INT32_MIN;
    static constexpr int MAX_VALUE = INT32_MAX;

    constexpr Integer() noexcept : value(0) {}
    constexpr Integer(int32_t v) noexcept : value(v) {}

    constexpr operator int() const noexcept { return value; }
    constexpr Integer& operator=(int32_t v) noexcept { value = v; return *this; }

    constexpr Integer& operator+=(int32_t v) noexcept { value += v; return *this; }
    constexpr Integer& operator*=(int32_t v) noexcept { value *= v; return *this; }

    constexpr Integer operator+(const Integer& o) const noexcept { return Integer(value + o.value); }
    constexpr Integer operator*(const Integer& o) const noexcept { return Integer(value * o.value); }

    [[nodiscard]] std::string toString() const;
    [[nodiscard]] static std::string toString(int v);

    static int parseInt(const std::string& s);
    static const Integer& valueOf(int v);

    constexpr bool operator==(const Integer& other) const noexcept { return value == other.value; }
    constexpr bool operator!=(const Integer& other) const noexcept { return value != other.value; }

    friend std::ostream& operator<<(std::ostream& os, const Integer& i) {return os << static_cast<int>(i);}
};