#pragma once
#include <string>
#include <vector>
#include <ostream>

class String {
    std::string inner;
public:

    String() = default;
    String(const char* s) : inner(s) {}
    String(const std::string& s) : inner(s) {}
    String(std::string&& s) : inner(std::move(s)) {}

    String& operator=(const std::string& s);
    String& operator=(const char* s);

    operator std::string() const;
    const std::string& toStd() const;

    size_t length() const;
    bool isEmpty() const;
    bool empty() const;
    char charAt(size_t idx) const;
    char charAtSafe(size_t idx, char fallback = '\0') const;

    String substring(size_t start) const;
    String substring(size_t start, size_t end) const;
    bool contains(const String& other) const;
    bool startsWith(const String& prefix) const;
    bool endsWith(const String& suffix) const;
    int indexOf(const String& sub) const;

    String replace(const String& from, const String& to) const;
    String removeAll(const String& target) const;
    String trim() const;
    String toUpperCase() const;
    String toLowerCase() const;

    bool equals(const String& other) const;
    bool equalsIgnoreCase(const String& other) const;
    bool operator==(const String& o) const;
    bool operator!=(const String& o) const;

    std::vector<String> split(char delimiter) const;
    static String join(const std::vector<String>& parts, const String& delimiter);

    int toInt() const;
    double toDouble() const;

    String operator+(const String& o) const;

    template<typename T>
    static String valueOf(const T& v) {
        return String(std::to_string(v));
    }
};

inline std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.toStd();
    return os;
}
