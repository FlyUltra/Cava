#pragma once
#include <string>
#include <memory>
#include <ostream>

class Boolean {
    bool value;

    static std::unique_ptr<Boolean> TRUE;
    static std::unique_ptr<Boolean> FALSE;
    static void initCache();

public:
    static constexpr bool TRUE_VALUE = true;
    static constexpr bool FALSE_VALUE = false;

    Boolean() : value(false) {}
    Boolean(bool v) : value(v) {}

    Boolean(const Boolean& other) = default;
    Boolean& operator=(const Boolean& other) = default;

    operator bool() const { return value; }

    bool get() const { return value; }

    int compareTo(const Boolean& other) const;
    bool equals(const Boolean& other) const;
    bool operator==(const Boolean& other) const;
    bool operator!=(const Boolean& other) const;

    std::size_t hashCode() const;

    static Boolean valueOf(bool v);
    static bool parseBoolean(const std::string& s);
    static std::string toString(bool v);

    bool booleanValue() const { return value; }
    static Boolean& TRUE_INSTANCE();
    static Boolean& FALSE_INSTANCE();

    friend std::ostream& operator<<(std::ostream& os, const Boolean& b);
};
