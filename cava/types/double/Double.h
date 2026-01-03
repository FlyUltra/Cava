#pragma once
#include <string>
#include <memory>
#include <ostream>
#include <limits>

class Double {
    double value;

    static std::unique_ptr<Double> POSITIVE_INFINITY;
    static std::unique_ptr<Double> NEGATIVE_INFINITY;
    static std::unique_ptr<Double> NaN;
    static std::unique_ptr<Double> ZERO;
    static std::unique_ptr<Double> ONE;
    static void initCache();

public:
    static constexpr double MIN_VALUE = std::numeric_limits<double>::min();
    static constexpr double MAX_VALUE = std::numeric_limits<double>::max();
    static constexpr double POSITIVE_INFINITY_VALUE = std::numeric_limits<double>::infinity();
    static constexpr double NEGATIVE_INFINITY_VALUE = -std::numeric_limits<double>::infinity();
    static constexpr double NaN_VALUE = std::numeric_limits<double>::quiet_NaN();

    Double() : value(0.0) {}
    Double(double v) : value(v) {}

    explicit Double(int v) : value(static_cast<double>(v)) {}
    explicit Double(long long v) : value(static_cast<double>(v)) {}
    explicit Double(float v) : value(static_cast<double>(v)) {}

    Double(const Double& other) = default;
    Double& operator=(const Double& other) = default;

    operator double() const { return value; }

    double get() const { return value; }

    int compareTo(const Double& other) const;
    bool equals(const Double& other) const;
    bool operator==(const Double& other) const;
    bool operator!=(const Double& other) const;

    std::size_t hashCode() const;

    static Double valueOf(double v);
    static double parseDouble(const std::string& s);
    static std::string toString(double v);

    static bool isNaN(double v);
    static bool isInfinite(double v);
    static bool isFinite(double v);

    bool isNaN() const;
    bool isInfinite() const;
    bool isFinite() const;

    static Double& POSITIVE_INFINITY_INSTANCE();
    static Double& NEGATIVE_INFINITY_INSTANCE();
    static Double& NaN_INSTANCE();

    friend std::ostream& operator<<(std::ostream& os, const Double& d);
};
