#pragma once
#include <string>
#include <memory>
#include <ostream>

class Byte {
    int8_t value;

    static std::unique_ptr<Byte> cache[];
    static constexpr int CACHE_LOW = -128;
    static constexpr int CACHE_HIGH = 127;
    static void initCache();

public:
    static constexpr int8_t MIN_VALUE = INT8_MIN;
    static constexpr int8_t MAX_VALUE = INT8_MAX;

    Byte() : value(0) {}
    Byte(int8_t v) : value(v) {}

    explicit Byte(int v);

    Byte(const Byte& other) = default;
    Byte& operator=(const Byte& other) = default;

    operator int8_t() const { return value; }

    int8_t get() const { return value; }

    int compareTo(const Byte& other) const;
    bool equals(const Byte& other) const;
    bool operator==(const Byte& other) const;
    bool operator!=(const Byte& other) const;

    std::size_t hashCode() const;

    static Byte valueOf(int8_t v);
    static int8_t parseByte(const std::string& s);
    static std::string toString(int8_t v);

    friend std::ostream& operator<<(std::ostream& os, const Byte& b);
};
