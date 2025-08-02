# Cava Integer Wrapper – Ergonomics with Measured Performance in C++

A lightweight `Integer` wrapper around `int32_t` that delivers Java-like ergonomics (e.g. `Integer a = 1; a += 2;`) while keeping overhead minimal. This module is designed to be safe, convenient, and measurable—showing real trade-offs between usability and speed.

___

## Features

- Wrapper over `int32_t` with implicit conversion to `int`
- In-place arithmetic: `+= int`, `+= Integer`, `*= int`, `*= Integer`
- Non-in-place: `operator+`, `operator*`
- Fast string conversion using `toString()` (via `std::to_chars`)
- Safe cache for small integers `[-128..127]` with `valueOf(int)`
- Parsing from string with strict validation: `parseInt`
- Stream output via overloaded `operator<<`

___

## Design Decisions

___

### Ergonomics vs Performance
The wrapper gives readable, expressive code without blindly sacrificing speed. In performance-critical loops, you can accumulate in a raw `int` and convert once:
```c++
int tmp = 0;
for (int i = 0; i < N; ++i) tmp += i;
Integer a = tmp; // one conversion
```

___

### Cache (`valueOf`)

* Static, no heap allocations, thread-safe initialization.
* Returns a reference for values in `[-128,127]` to avoid unnecessary temporaries.
* Outside that range, returns a thread-local temporary by value.

___

### String Conversion

* `toString()` allocates a `std::string` but uses `std::to_chars` for speed.
* For hot paths, a zero-allocation variant (`toStringInto`) can be added to avoid heap activity.

___

### Safety & Optimization

* Uses `constexpr` / `noexcept` where appropriate to enable inlining and elimination.
* `parseInt` only accepts fully valid integer strings (strict parsing).
* Simple `operator<<` for easy debugging and logging.

___

## Benchmark Summary (vs primitive `int`)

Benchmarks use a loop with `N = 100000` iterations, warmup.

| Operation               | `int` (mean) | `Integer` (mean) | Relative Overhead |
| ----------------------- | -----------: | ---------------: | ----------------: |
| assignment              |      36.9 ns |          36.8 ns |        ≈1× (none) |
| addition (`+= i`)       |   178,903 ns |       223,171 ns |    \~1.24× slower |
| multiplication (`*= i`) |   250,258 ns |       265,164 ns |    \~1.06× slower |
| to\_string              |      79.5 ns |         101.9 ns |    \~1.28× slower |

___

### Key Takeaways

* **Assignment** is essentially free; wrapper imposes no cost.
* **Addition** with `a += i` has a modest overhead (\~24%); can be eradicated by accumulating in `int` and converting once.
* **Multiplication** is nearly on par with primitive `int`.
* **String conversion** pays allocation cost; zero-allocation alternatives are advisable in tight loops.

___

## Usage Example

```c++
#include "Integer.hpp"
#include <iostream>

int main() {
    Integer a = Integer::valueOf(10);
    a += 5;
    std::cout << "Result: " << a << "\n";

    // High-performance accumulation pattern:
    int tmp = 0;
    for (int i = 0; i < 100000; ++i) tmp += i;
    Integer optimized = tmp; // minimal overhead
}
```

___

## Benchmarking Snippet (simplified)

```c++
int N = 100000;
benchmark("Integer addition", [&]() {
    Integer a = 1;
    for (int i = 0; i < N; ++i) {
        a += i; // optimized path
    }
    volatile Integer x = a;
}, 10, 200);
```

Compile with:

```bash
g++ -std=c++20 -O3 -march=native -flto main.cpp Integer.cpp -o bench
```

___

## Trade-offs

| Benefit                              | Cost                                                       |
| ------------------------------------ | ---------------------------------------------------------- |
| Ergonomic wrapper with intuitive API | Small runtime overhead on addition                         |
| Safe cached small integer pooling    | Slight complexity vs raw `int`                             |
| Fast string conversion core logic    | `toString()` still allocates (add `toStringInto` to avoid) |

___

## Recommendations

* Use `Integer` directly in most code with `a += i` / `a *= i` for clarity.
* In extremely hot loops: accumulate using primitives and convert once.
* Replace `toString()` with a zero-allocation variant in performance-sensitive output paths.
* Use `valueOf` for repeated small constant usage to leverage canonical references.

___

## Reproduction

1. Clone the repository.
2. Build with optimizations:

```bash
   mkdir build && cd build
   cmake .. -DCMAKE_CXX_FLAGS="-std=c++20 -O3 -march=native -flto" # Can be used
   make
   ```

___

3. Run benchmarks and compare:

* `int` vs `Integer += int`
* Raw accumulation vs wrapper accumulation
* `toString()` vs zero-allocation `toStringInto` (if added)

___

## Conclusion

This module demonstrates how to design a higher-level type with ergonomic syntax while retaining close-to-metal performance. All behavior is measured, trade-offs are explicit, and fallback patterns ensure minimal cost where it matters most.


