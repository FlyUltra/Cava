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

    operator std::string() const { return inner; }
    const std::string& toStd() const { return inner; }

    size_t length() const { return inner.size(); }
    bool isEmpty() const { return inner.empty(); }

    char charAt(size_t idx) const { return inner.at(idx); }

    String substring(size_t start) const {
        if (start >= inner.size()) return String("");
        return String(inner.substr(start));
    }
    String substring(size_t start, size_t end) const {
        if (start >= inner.size() || start >= end) return String("");
        size_t len = std::min(end, inner.size()) - start;
        return String(inner.substr(start, len));
    }

    bool contains(const String& other) const {
        return inner.find(other.inner) != std::string::npos;
    }
    bool startsWith(const String& prefix) const {
        return inner.rfind(prefix.inner, 0) == 0;
    }
    bool endsWith(const String& suffix) const {
        if (suffix.inner.size() > inner.size()) return false;
        return inner.compare(inner.size() - suffix.inner.size(), suffix.inner.size(), suffix.inner) == 0;
    }

    int indexOf(const String& sub) const {
        auto pos = inner.find(sub.inner);
        if (pos == std::string::npos) return -1;
        return static_cast<int>(pos);
    }

    String replace(const String& from, const String& to) const {
        std::string result = inner;
        size_t pos = 0;
        while ((pos = result.find(from.inner, pos)) != std::string::npos) {
            result.replace(pos, from.inner.size(), to.inner);
            pos += to.inner.size();
        }
        return String(std::move(result));
    }

    String trim() const {
        size_t start = 0;
        while (start < inner.size() && isspace(static_cast<unsigned char>(inner[start]))) start++;
        size_t end = inner.size();
        while (end > start && isspace(static_cast<unsigned char>(inner[end - 1]))) end--;
        return substring(start, end);
    }

    String toUpperCase() const {
        std::string s = inner;
        for (char& c : s) c = static_cast<char>(::toupper(static_cast<unsigned char>(c)));
        return String(std::move(s));
    }
    String toLowerCase() const {
        std::string s = inner;
        for (char& c : s) c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
        return String(std::move(s));
    }

    std::vector<String> split(char delimiter) const {
        std::vector<String> out;
        size_t pos = 0;
        while (pos <= inner.size()) {
            size_t next = inner.find(delimiter, pos);
            if (next == std::string::npos) next = inner.size();
            out.emplace_back(inner.substr(pos, next - pos));
            pos = next + 1;
        }
        return out;
    }

    String operator+(const String& o) const { return String(inner + o.inner); }
    bool operator==(const String& o) const { return inner == o.inner; }
    bool operator!=(const String& o) const { return inner != o.inner; }

    template<typename T>
    static String valueOf(const T& v) {
        return String(std::to_string(v));
    }
};

inline std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.toStd();
    return os;
}