#include "Character.h"
#include <stdexcept>
#include <mutex>
#include <cctype>

std::unique_ptr<Character> Character::cache[Character::CACHE_HIGH - Character::CACHE_LOW + 1] = { nullptr };
static std::once_flag charCacheFlag;

void Character::initCache() {
    for (int i = CACHE_LOW; i <= CACHE_HIGH; ++i) {
        cache[i - CACHE_LOW] = std::make_unique<Character>(static_cast<char>(i));
    }
}

Character Character::valueOf(char v) {
    std::call_once(charCacheFlag, Character::initCache);
    int idx = static_cast<unsigned char>(v) - CACHE_LOW;
    if (static_cast<unsigned char>(v) >= CACHE_LOW && static_cast<unsigned char>(v) <= CACHE_HIGH) {
        return *cache[idx];
    }
    return Character(v);
}

Character::Character(int v) {
    if (v < static_cast<int>(MIN_VALUE) || v > static_cast<int>(MAX_VALUE)) {
        throw std::out_of_range("Character value out of range: " + std::to_string(v));
    }
    value = static_cast<char>(v);
}

char Character::parseChar(const std::string& s) {
    if (s.empty()) {
        throw std::invalid_argument("Empty string");
    }
    return s[0];
}

std::string Character::toString(char v) {
    return std::string(1, v);
}

int Character::compareTo(const Character& other) const {
    return (value < other.value) ? -1 : (value > other.value ? 1 : 0);
}

bool Character::equals(const Character& other) const {
    return value == other.value;
}

bool Character::operator==(const Character& other) const {
    return value == other.value;
}

bool Character::operator!=(const Character& other) const {
    return value != other.value;
}

std::size_t Character::hashCode() const {
    return std::hash<char>()(value);
}

bool Character::isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

bool Character::isLetter(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) != 0;
}

bool Character::isLetterOrDigit(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) != 0;
}

bool Character::isLowerCase(char c) {
    return std::islower(static_cast<unsigned char>(c)) != 0;
}

bool Character::isUpperCase(char c) {
    return std::isupper(static_cast<unsigned char>(c)) != 0;
}

bool Character::isWhitespace(char c) {
    return std::isspace(static_cast<unsigned char>(c)) != 0;
}

char Character::toLowerCase(char c) {
    return std::tolower(static_cast<unsigned char>(c));
}

char Character::toUpperCase(char c) {
    return std::toupper(static_cast<unsigned char>(c));
}

std::ostream& operator<<(std::ostream& os, const Character& c) {
    os << c.value;
    return os;
}
