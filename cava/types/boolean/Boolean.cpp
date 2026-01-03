#include "Boolean.h"
#include <stdexcept>
#include <mutex>

std::unique_ptr<Boolean> Boolean::TRUE = nullptr;
std::unique_ptr<Boolean> Boolean::FALSE = nullptr;
static std::once_flag booleanCacheFlag;

void Boolean::initCache() {
    TRUE = std::make_unique<Boolean>(true);
    FALSE = std::make_unique<Boolean>(false);
}

Boolean Boolean::valueOf(bool v) {
    std::call_once(booleanCacheFlag, Boolean::initCache);
    return v ? *TRUE : *FALSE;
}

Boolean& Boolean::TRUE_INSTANCE() {
    std::call_once(booleanCacheFlag, Boolean::initCache);
    return *TRUE;
}

Boolean& Boolean::FALSE_INSTANCE() {
    std::call_once(booleanCacheFlag, Boolean::initCache);
    return *FALSE;
}

bool Boolean::parseBoolean(const std::string& s) {
    if (s.size() == 4) {
        std::string lower;
        lower.resize(4);
        for (int i = 0; i < 4; i++) {
            lower[i] = std::tolower(s[i]);
        }
        return (lower == "true");
    }
    return false;
}

std::string Boolean::toString(bool v) {
    return v ? "true" : "false";
}

int Boolean::compareTo(const Boolean& other) const {
    return (value == other.value) ? 0 : (value ? 1 : -1);
}

bool Boolean::equals(const Boolean& other) const {
    return value == other.value;
}

bool Boolean::operator==(const Boolean& other) const {
    return value == other.value;
}

bool Boolean::operator!=(const Boolean& other) const {
    return value != other.value;
}

std::size_t Boolean::hashCode() const {
    return std::hash<bool>()(value);
}

std::ostream& operator<<(std::ostream& os, const Boolean& b) {
    os << (b.value ? "true" : "false");
    return os;
}
