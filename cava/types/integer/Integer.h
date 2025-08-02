#pragma once
#include <string>
#include <memory>

class Integer {
public:
    static constexpr int MIN_VALUE = INT32_MIN;
    static constexpr int MAX_VALUE = INT32_MAX;

    Integer(int v) : value(v) {}

    operator int() const { return value; }

    int compareTo(const Integer& other) const;
    bool equals(const Integer& other) const;

    std::size_t hashCode() const;

    static Integer valueOf(int v);
    static int parseInt(const std::string& s);
    static std::string toStringStatic(int v);

    static int max(int a, int b);
    static int min(int a, int b);

private:
    int value;
    static Integer* cache[];
    static constexpr int CACHE_LOW = -128;
    static constexpr int CACHE_HIGH = 127;
    static void initCache();
    static bool cacheInitialized;
};