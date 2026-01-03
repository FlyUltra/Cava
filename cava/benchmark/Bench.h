#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

struct Stats {
    double mean;
    double median;
    double min;
    double max;
    double stddev;
};

template<typename T>
inline void doNotOptimizeAway(T&& value) {
    asm volatile("" : "+r" (value));
}

inline Stats compute_stats(std::vector<double>& samples) {
    std::sort(samples.begin(), samples.end());
    double sum = std::accumulate(samples.begin(), samples.end(), 0.0);
    double mean = sum / samples.size();
    double median = samples.size() % 2 == 0
        ? (samples[samples.size()/2 - 1] + samples[samples.size()/2]) / 2.0
        : samples[samples.size()/2];
    double min = samples.front();
    double max = samples.back();
    double variance = 0;
    for (double s : samples) {
        double d = s - mean;
        variance += d * d;
    }
    variance /= samples.size();
    double stddev = std::sqrt(variance);
    return {mean, median, min, max, stddev};
}

template<typename F>
Stats benchmark(const std::string& name, F f, int warmup_iters = 500, int iters = 500) {
    for (int i = 0; i < warmup_iters; ++i) {
        f();
    }

    std::vector<double> samples;
    samples.reserve(iters);
    for (int i = 0; i < iters; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        f();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> diff = end - start;
        samples.push_back(diff.count());
    }

    Stats s = compute_stats(samples);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Benchmark \"" << name << "\" over " << iters << " iters:\n";
    std::cout << "  mean    : " << s.mean << " ns\n";
    std::cout << "  median  : " << s.median << " ns\n";
    std::cout << "  min     : " << s.min << " ns\n";
    std::cout << "  max     : " << s.max << " ns\n";
    std::cout << "  stddev  : " << s.stddev << " ns\n";
    std::cout << "\n";
    return s;
}
