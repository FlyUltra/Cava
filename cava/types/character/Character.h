#pragma once
#include <string>
#include <memory>
#include <ostream>

class Character {
    char value;

    static std::unique_ptr<Character> cache[];
    static constexpr int CACHE_LOW = 0;
    static constexpr int CACHE_HIGH = 127;
    static void initCache();

public:
    static constexpr char MIN_VALUE = CHAR_MIN;
    static constexpr char MAX_VALUE = CHAR_MAX;

    Character() : value('\0') {}
    Character(char v) : value(v) {}

    explicit Character(int v);

    Character(const Character& other) = default;
    Character& operator=(const Character& other) = default;

    operator char() const { return value; }

    char get() const { return value; }

    int compareTo(const Character& other) const;
    bool equals(const Character& other) const;
    bool operator==(const Character& other) const;
    bool operator!=(const Character& other) const;

    std::size_t hashCode() const;

    static Character valueOf(char v);
    static char parseChar(const std::string& s);
    static std::string toString(char v);

    static bool isDigit(char c);
    static bool isLetter(char c);
    static bool isLetterOrDigit(char c);
    static bool isLowerCase(char c);
    static bool isUpperCase(char c);
    static bool isWhitespace(char c);
    static char toLowerCase(char c);
    static char toUpperCase(char c);

    friend std::ostream& operator<<(std::ostream& os, const Character& c);
};
