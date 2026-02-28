#ifndef CAVA_OBJECT_H
#define CAVA_OBJECT_H

#include <string>
#include <ostream>
#include <variant>
#include <utility>
#include <functional>

class Object {
public:
    using Value = std::variant<std::monostate, int, long long, double, bool, std::string>;

private:
    Value internalValue;

public:
    Object() : internalValue(std::monostate{}) {}
    Object(int v) : internalValue(v) {}
    Object(long long v) : internalValue(v) {}
    Object(double v) : internalValue(v) {}
    Object(bool v) : internalValue(v) {}
    Object(const char* v) : internalValue(std::string(v)) {}
    Object(std::string v) : internalValue(std::move(v)) {}

    bool operator==(const Object& other) const {
        return internalValue == other.internalValue;
    }

    const Value& getValue() const { return internalValue; }

    virtual std::string toString() const {
        return std::visit([](auto&& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate>) return "null";
            else if constexpr (std::is_same_v<T, bool>) return arg ? "true" : "false";
            else if constexpr (std::is_same_v<T, std::string>) return arg;
            else return std::to_string(arg);
        }, internalValue);
    }

    friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
        os << obj.toString();
        return os;
    }
};

namespace std {
    template <>
    struct hash<Object> {
        size_t operator()(const Object& obj) const {
            return std::hash<Object::Value>{}(obj.getValue());
        }
    };
}

#endif