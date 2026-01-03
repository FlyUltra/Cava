#include "Double.h"
#include <stdexcept>
#include <mutex>
#include <limits>
#include <cmath>

std::unique_ptr<Double> Double::POSITIVE_INFINITY = nullptr;
std::unique_ptr<Double> Double::NEGATIVE_INFINITY = nullptr;
std::unique_ptr<Double> Double::NaN = nullptr;
std::unique_ptr<Double> Double::ZERO = nullptr;
std::unique_ptr<Double> Double::ONE = nullptr;
static std::once_flag doubleCacheFlag;

void Double::initCache() {
    POSITIVE_INFINITY = std::make_unique<Double>(POSITIVE_INFINITY_VALUE);
    NEGATIVE_INFINITY = std::make_unique<Double>(NEGATIVE_INFINITY_VALUE);
    NaN = std::make_unique<Double>(NaN_VALUE);
    ZERO = std::make_unique<Double>(0.0);
    ONE = std::make_unique<Double>(1.0);
}

Double Double::valueOf(double v) {
    std::call_once(doubleCacheFlag, Double::initCache);
    if (v == 0.0) return *ZERO;
    if (v == 1.0) return *ONE;
    if (v == POSITIVE_INFINITY_VALUE) return *POSITIVE_INFINITY;
    if (v == NEGATIVE_INFINITY_VALUE) return *NEGATIVE_INFINITY;
    if (std::isnan(v)) return *NaN;
    return Double(v);
}

Double& Double::POSITIVE_INFINITY_INSTANCE() {
    std::call_once(doubleCacheFlag, Double::initCache);
    return *POSITIVE_INFINITY;
}

Double& Double::NEGATIVE_INFINITY_INSTANCE() {
    std::call_once(doubleCacheFlag, Double::initCache);
    return *NEGATIVE_INFINITY;
}

Double& Double::NaN_INSTANCE() {
    std::call_once(doubleCacheFlag, Double::initCache);
    return *NaN;
}

double Double::parseDouble(const std::string& s) {
    try {
        return std::stod(s);
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid double: " + s);
    }
}

std::string Double::toString(double v) {
    if (std::isnan(v)) return "NaN";
    if (v == POSITIVE_INFINITY_VALUE) return "Infinity";
    if (v == NEGATIVE_INFINITY_VALUE) return "-Infinity";
    return std::to_string(v);
}

int Double::compareTo(const Double& other) const {
    if (std::isnan(value) && std::isnan(other.value)) return 0;
    if (std::isnan(value)) return 1; // NaN
    if (std::isnan(other.value)) return -1;
    return (value < other.value) ? -1 : (value > other.value ? 1 : 0);
}

bool Double::equals(const Double& other) const {
    if (std::isnan(value) && std::isnan(other.value)) return true;
    return value == other.value;
}

bool Double::operator==(const Double& other) const {
    return equals(other);
}

bool Double::operator!=(const Double& other) const {
    return !equals(other);
}

std::size_t Double::hashCode() const {
    return std::hash<double>()(value);
}

bool Double::isNaN(double v) {
    return std::isnan(v);
}

bool Double::isInfinite(double v) {
    return std::isinf(v);
}

bool Double::isFinite(double v) {
    return std::isfinite(v);
}

bool Double::isNaN() const {
    return std::isnan(value);
}

bool Double::isInfinite() const {
    return std::isinf(value);
}

bool Double::isFinite() const {
    return std::isfinite(value);
}

std::ostream& operator<<(std::ostream& os, const Double& d) {
    if (d.isNaN()) {
        os << "NaN";
    } else if (d.value == Double::POSITIVE_INFINITY_VALUE) {
        os << "Infinity";
    } else if (d.value == Double::NEGATIVE_INFINITY_VALUE) {
        os << "-Infinity";
    } else {
        os << d.value;
    }
    return os;
}
