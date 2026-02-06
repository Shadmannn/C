# K&R C 

This repository contains my personal solutions and experiments as I work through the classic book **"The C Programming Language" (2nd Edition)** by Brian Kernighan and Dennis Ritchie.

## Progress
- [ ] **Chapter 2:** Types, Operators, and Expressions (In Progress)

## Highlights

### Exercise 2-1: Variable Ranges
This program determines the ranges of various data types (char, short, int, long) using two methods:
1. **Standard Headers:** Utilizing `<limits.h>` and `<float.h>`.
2. **Direct Computation:** Calculating limits using bitwise operators like `~0` (NOT) and bit-shifting `>>`.

#### What I Learned:
* How to use specific format specifiers like `%lu` for unsigned long to avoid compiler warnings.
* The logic of **Two's Complement** and how bitwise operations interact with hardware memory limits.

### Section 2.3: Constants
This section explores how C handles fixed values, ranging from simple integers to complex string literals and enumeration constants.

Key Concepts Covered:
1. **Integer & Floating Constants:** Using suffixes (L, U, UL, F) to explicitly define data sizes and prevent overflow.
2. **Character Constants:** Understanding ASCII values and the difference between 'x' (an int value) and "x" (a string array).
3. **Escape Sequences:** Mastering non-graphic characters like \n, \t, and octal/hexadecimal escapes (\ooo, \xhh).
4. **String Literals:** The mechanics of null-termination (\0) and compile-time string concatenation.
5. **Enumeration Constants:** Using enum as a cleaner, type-aware alternative to #define.

What I Learned:
1. **Memory Efficiency:** How string constants are stored in read-only memory and accessed via pointers.
2. **The Power of sizeof:** Using this operator to write portable code that adapts to different system architectures (32-bit vs. 64-bit).
3. **Custom Implementation:** Developed my_strlen to manually traverse memory until the null terminator is reached, mimicking the standard library's behavior.

## How to Run
To compile and run any code or exercise (e.g., Exercise 2-1):
```bash
gcc ex2_1.c -o ex2_1 && ./ex2_1

