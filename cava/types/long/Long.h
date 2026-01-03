#pragma once
#include <string>
#include <memory>
#include <ostream>

class Long {
    long long value;

    static std::unique_ptr<Long> cache[];
    static constexpr long long CACHE_LOW = -128;
    static constexpr long long CACHE_HIGH = 127;
    static void initCache();

public:
    static constexpr long long MIN_VALUE = LLONG_MIN;
    static constexpr long long MAX_VALUE = LLONG_MAX;

    Long() : value(0) {}
    Long(long long v) : value(v) {}
    explicit Long(long double v);

    Long(const Long& other) = default;
    Long& operator=(const Long& other) = default;

    operator long long() const { return value; }

    long long get() const { return value; }

    int compareTo(const Long& other) const;
    bool equals(const Long& other) const;
    bool operator==(const Long& other) const;
    bool operator!=(const Long& other) const;

    std::size_t hashCode() const;

    static Long valueOf(long long v);
    static long long parseLong(const std::string& s);
    static std::string toString(long long v);

    friend std::ostream& operator<<(std::ostream& os, const Long& l);
};
