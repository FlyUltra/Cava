#include "String.h"
#include <algorithm>
#include <sstream>
#include <cctype>

String& String::operator=(const std::string& s) {
    inner = s;
    return *this;
}

String& String::operator=(const char* s) {
    inner = s;
    return *this;
}

String::operator std::string() const {
    return inner;
}

const std::string& String::toStd() const {
    return inner;
}

size_t String::length() const {
    return inner.size();
}

bool String::isEmpty() const {
    return inner.empty();
}

bool String::empty() const {
    return inner.empty();
}

char String::charAt(size_t idx) const {
    return inner.at(idx);
}

char String::charAtSafe(size_t idx, char fallback) const {
    return idx < inner.size() ? inner[idx] : fallback;
}

String String::substring(size_t start) const {
    if (start >= inner.size()) return String("");
    return String(inner.substr(start));
}

String String::substring(size_t start, size_t end) const {
    if (start >= inner.size() || start >= end) return String("");
    size_t len = std::min(end, inner.size()) - start;
    return String(inner.substr(start, len));
}

bool String::contains(const String& other) const {
    return inner.find(other.inner) != std::string::npos;
}

bool String::startsWith(const String& prefix) const {
    return inner.rfind(prefix.inner, 0) == 0;
}

bool String::endsWith(const String& suffix) const {
    if (suffix.inner.size() > inner.size()) return false;
    return inner.compare(inner.size() - suffix.inner.size(), suffix.inner.size(), suffix.inner) == 0;
}

int String::indexOf(const String& sub) const {
    auto pos = inner.find(sub.inner);
    return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

String String::replace(const String& from, const String& to) const {
    std::string result = inner;
    size_t pos = 0;
    while ((pos = result.find(from.inner, pos)) != std::string::npos) {
        result.replace(pos, from.inner.size(), to.inner);
        pos += to.inner.size();
    }
    return String(std::move(result));
}

String String::removeAll(const String& target) const {
    return replace(target, "");
}

String String::trim() const {
    size_t start = 0;
    while (start < inner.size() && isspace(static_cast<unsigned char>(inner[start]))) start++;
    size_t end = inner.size();
    while (end > start && isspace(static_cast<unsigned char>(inner[end - 1]))) end--;
    return substring(start, end);
}

String String::toUpperCase() const {
    std::string s = inner;
    for (char& c : s)
        c = static_cast<char>(::toupper(static_cast<unsigned char>(c)));
    return String(std::move(s));
}

String String::toLowerCase() const {
    std::string s = inner;
    for (char& c : s)
        c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
    return String(std::move(s));
}

std::vector<String> String::split(char delimiter) const {
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

String String::join(const std::vector<String>& parts, const String& delimiter) {
    if (parts.empty()) return "";
    std::string result = parts[0].inner;
    for (size_t i = 1; i < parts.size(); ++i) {
        result += delimiter.inner + parts[i].inner;
    }
    return String(result);
}

bool String::equals(const String& other) const {
    return inner == other.inner;
}

bool String::equalsIgnoreCase(const String& other) const {
    return toLowerCase().inner == other.toLowerCase().inner;
}

bool String::operator==(const String& o) const {
    return inner == o.inner;
}

bool String::operator!=(const String& o) const {
    return inner != o.inner;
}

String String::operator+(const String& o) const {
    return String(inner + o.inner);
}

int String::toInt() const {
    return std::stoi(inner);
}

double String::toDouble() const {
    return std::stod(inner);
}
