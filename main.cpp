#include <iostream>
#include "cava/benchmark/bench.h"
#include <string>
#include <sstream>
#include <charconv>
#include <vector>

#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <cmath>

#include "cava/System.h"
#include "cava/macros/macros.h"
#include "cava/types/integer/Integer.h"

template<typename F>
double measure_once(F f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> diff = end - start;
    return diff.count();
}

template<typename F>
double benchmark(const std::string& name, F f, int warmup = 10, int iters = 1000) {
    for (int i = 0; i < warmup; ++i) f();
    std::vector<double> samples;
    samples.reserve(iters);
    for (int i = 0; i < iters; ++i) {
        samples.push_back(measure_once(f));
    }
    double sum = std::accumulate(samples.begin(), samples.end(), 0.0);
    double mean = sum / samples.size();
    std::sort(samples.begin(), samples.end());
    double median = samples[samples.size()/2];
    std::cout << name << " — mean: " << mean << " ns, median: " << median << " ns\n";
    return mean;
}

int main() {
    const int N = 1000000;

    benchmark("int assignment", [&]() {
        const int a = 42;
        const int b = a;
        const volatile int c = b;
        (void)c;
    });

    benchmark("Integer assignment", [&]() {
        Integer a = 42;
        Integer b = a;
        volatile Integer c = b;
        (void)c;
    });

    // 2. addition
    benchmark("int addition", [&]() {
        int a = 1;
        for (int i = 0; i < N; ++i) {
            a += i;
        }
        const volatile int x = a;
        (void)x;
    });

    benchmark("Integer addition", [&]() {
        Integer a = 1;
        for (int i = 0; i < N; ++i) {
            a += i;
        }
        volatile Integer x = a;
        (void)x;
    });

    benchmark("int multiplication", [&]() {
        int a = 2;
        for (int i = 1; i < N; ++i) {
            a = a * i;
        }
        const volatile int x = a;
        (void)x;
    });

    benchmark("Integer multiplication", [&]() {
        Integer a = 2;
        for (int i = 1; i < N; ++i) {
            a *= i;
        }
        volatile Integer x = a;
        (void)x;
    });

    // 4. to string
    benchmark("int to_string", [&]() {
        const int v = 123456;
        volatile std::string s = std::to_string(v);
        (void)s;
    });

    benchmark("Integer toString", [&]() {
        const Integer v = 123456;
        volatile std::string s = v.toString();
        (void)s;
    });

    return 0;
}
