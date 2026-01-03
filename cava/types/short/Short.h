#pragma once
#include <string>
#include <memory>
#include <ostream>

class Short {
    short value;

    static std::unique_ptr<Short> cache[];
    static constexpr int CACHE_LOW = -128;
    static constexpr int CACHE_HIGH = 127;
    static void initCache();

public:
    static constexpr short MIN_VALUE = INT16_MIN;
    static constexpr short MAX_VALUE = INT16_MAX;

    Short() : value(0) {}

    Short(short v) : value(v) {}

    explicit Short(int v);

    Short(const Short& other) = default;
    Short& operator=(const Short& other) = default;

    operator short() const { return value; }

    short get() const { return value; }

    int compareTo(const Short& other) const;
    bool equals(const Short& other) const;
    bool operator==(const Short& other) const;
    bool operator!=(const Short& other) const;

    std::size_t hashCode() const;

    static Short valueOf(short v);
    static short parseShort(const std::string& s);
    static std::string toString(short v);

    friend std::ostream& operator<<(std::ostream& os, const Short& s);
};
