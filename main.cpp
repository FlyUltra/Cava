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
#include "cava/collections/HashMap.h"
#include "cava/macros/macros.h"
#include "cava/types/integer/Integer.h"
#include "cava/types/object/Object.h"

int main() {

    HashMap<Object, Object> map;

    map.put("ID_1", 500);
    map.put(10, "Deset");
    map.put("Aktivni", true);

    System::println(map.get("ID_1"));
    System::println(map.get(10));
    System::println(map.get("Aktivni"));

    if (map.containsKey("Neexistuje")) {
        System::println("Tohle se nevypise");
    }




    // benchmark("int assignment", [&]() {
    //     const int a = 42;
    //     const int b = a;
    //     const volatile int c = b;
    //     (void)c;
    // });
    //
    // benchmark("Integer assignment", [&]() {
    //     Integer a = 42;
    //     Integer b = a;
    //     volatile Integer c = b;
    //     (void)c;
    // });
    //
    //
    // // 2. addition
    // benchmark("int addition", [&]() {
    //     int a = 1;
    //     for (int i = 0; i < N; ++i) {
    //         a += i;
    //     }
    //     const volatile int x = a;
    //     (void)x;
    // });
    //
    // benchmark("Integer addition", [&]() {
    //     Integer a = 1;
    //     for (int i = 0; i < N; ++i) {
    //         a += i;
    //     }
    //     volatile Integer x = a;
    //     (void)x;
    // });
    //
    // benchmark("int multiplication", [&]() {
    //     int a = 2;
    //     for (int i = 1; i < N; ++i) {
    //         a = a * i;
    //     }
    //     const volatile int x = a;
    //     (void)x;
    // });
    //
    // benchmark("Integer multiplication", [&]() {
    //     Integer a = 2;
    //     for (int i = 1; i < N; ++i) {
    //         a *= i;
    //     }
    //     volatile Integer x = a;
    //     (void)x;
    // });
    //
    // // 4. to string
    // benchmark("int to_string", [&]() {
    //     const int v = 123456;
    //     volatile std::string s = std::to_string(v);
    //     (void)s;
    // });
    //
    // benchmark("Integer toString", [&]() {
    //     const Integer v = 123456;
    //     volatile std::string s = v.toString();
    //     (void)s;
    // });

    return 0;
}
