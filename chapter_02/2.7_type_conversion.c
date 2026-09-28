/*
 * General Rule:
 * When an operator has operands of different types, they are converted
 * to a common type. Automatic conversions only convert a "narrower"
 * operand into a "wider" one without losing information (e.g., int to float).
 * Conversions that might lose information (assigning long to short, or float
 * to int) may draw a compiler warning, but are legally permitted.
 */

#include <stdio.h>
#include <ctype.h>  // Standard library header for character classification/conversion
#include <math.h>   // Standard library header for math functions like sqrt()

/* ----------------------------------------------------------------------------
 * 1. INTEGRAL PROMOTIONS: CHAR & INT CONVERSIONS
 * ----------------------------------------------------------------------------
 * A 'char' is simply a small integer. Hence, 'char' variables can be freely
 * used in integer arithmetic expressions.
 */

/*
 * Example: Converting a string of digits into its numeric integer equivalent.
 * Demonstrates 'char' arithmetic: s[i] - '0' yields numeric value 0 through 9
 * because character representations of '0' through '9' are contiguous.
 */
int atoi_k_and_r(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
        n = 10 * n + (s[i] - '0');
    }
    return n;
}

/*
 * Example: Convert character to lower case for ASCII character set.
 * Returns the character unchanged if it is not an uppercase letter.
 */
int lower_ascii_only(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

/*
 * NOTE ON CHAR SIGN EXTENSION:
 * - C does not specify whether plain 'char' variables are signed or unsigned.
 * - Machine-dependency: Converting a 'char' with a leftmost bit of 1 to 'int'
 *   may produce a negative integer on machines that perform sign-extension,
 *   or a positive integer on machines that zero-fill the high order bits.
 * - Portable Code Rule: Guaranteed printing characters are always positive,
 *   but non-character data stored in 'char' should explicitly specify 'signed'
 *   or 'unsigned'.
 */

/* ----------------------------------------------------------------------------
 * 2. IMPLICIT ARITHMETIC CONVERSIONS (USUAL ARITHMETIC CONVERSIONS)
 * ----------------------------------------------------------------------------
 * In binary operations with operands of different types, the lower type
 * is promoted to the higher type before execution.
 *
 * Informal Promotion Hierarchy (When no unsigned operands are involved):
 *   1. If either operand is long double -> convert other to long double
 *   2. Else, if either operand is double      -> convert other to double
 *   3. Else, if either operand is float       -> convert other to float
 *   4. Else, convert char and short to int
 *   5. Then, if either operand is long        -> convert other to long
 *
 * NOTE:
 * - Floats in expressions are NOT automatically converted to double in ANSI C
 *   unless passed to functions expecting double precision.
 * - Comparisons between signed and unsigned types are machine-dependent
 *   because they depend on the bit-width of integer types (e.g., -1L < 1U
 *   might evaluate differently depending on int vs long bit-width).
 */

/* ----------------------------------------------------------------------------
 * 3. ASSIGNMENT CONVERSIONS & TRUNCATION
 * ----------------------------------------------------------------------------
 * Conversions occur across assignments; the right side is converted to the type
 * of the left-hand variable, which determines the type of the result.
 */
void demonstration_assignment_conversions(void)
{
    int i;
    char c;
    float x;

    /* No loss of information: int to char to int */
    i = c;
    c = i;

    /* Dropping High-Order Bits:
     * Converting a longer integer to a shorter integer or char drops excess
     * high-order bits.
     */

    /* Truncation: float to int truncates the fractional part */
    x = 3.89f;
    i = (int)x; /* i receives 3 */
}

/* ----------------------------------------------------------------------------
 * 4. EXPLICIT TYPE CASTS
 * ----------------------------------------------------------------------------
 * Explicit conversions can be coerced using the unary cast operator:
 *   (type-name) expression
 */

/* Pseudorandom number generator example utilizing explicit cast */
static unsigned long int next = 1;

int rand_k_and_r(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768; /* Casts resulting calculation */
}

void srand_k_and_r(unsigned int seed)
{
    next = seed;
}

void demonstrate_casts(void)
{
    int n = 2;

    /*
     * Unary cast forces 'n' to double before passing it to sqrt().
     * Note: n itself remains an integer variable.
     *
     * BUILD NOTE:
     * sqrt() lives in the math library (libm), which is NOT linked by
     * default. Compiling without "-lm" produces:
     *
     *   undefined reference to `sqrt'
     *
     * Fix: add -lm at the END of the gcc command. See section 6 below.
     */
    double root2 = sqrt((double) n);

    /*
     * Function Prototypes:
     * When a function prototype is declared (e.g., double sqrt(double)),
     * calling sqrt(2) automatically coerces the integer 2 into double 2.0
     * without needing an explicit cast.
     */
}

/* ----------------------------------------------------------------------------
 * 5. K&R EXERCISE 2-3 SOLUTION
 * ----------------------------------------------------------------------------
 * Exercise 2-3: Write a function htoi(s), which converts a string of
 * hexadecimal digits (including optional 0x or 0X) into its equivalent
 * integer value. Allowable digits: 0-9, a-f, A-F.
 */
int htoi(char s[])
{
    int i = 0;
    int n = 0;
    int hex_digit;
    int in_hex = 1;

    /* Skip optional leading "0x" or "0X" */
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    }

    for (; in_hex; ++i) {
        if (s[i] >= '0' && s[i] <= '9') {
            hex_digit = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            hex_digit = s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            hex_digit = s[i] - 'A' + 10;
        } else {
            in_hex = 0; /* Reached end of valid hex digits */
        }

        if (in_hex) {
            n = 16 * n + hex_digit;
        }
    }

    return n;
}

/* ----------------------------------------------------------------------------
 * 6. LINKING EXTERNAL LIBRARIES (WHY sqrt() FAILS WITHOUT -lm)
 * ----------------------------------------------------------------------------
 *
 * SYMPTOM
 * -------
 *   $ gcc 2.7_type_conversion.c -o 2.7_type_conversion
 *   /usr/bin/.../ld.bfd: ...: undefined reference to `sqrt'
 *   collect2: error: ld returned 1 exit status
 *
 * WHAT ACTUALLY HAPPENED
 * ----------------------
 *   Compilation and linking are two SEPARATE stages:
 *
 *     .c  --[compiler]-->  .o  --[linker]-->  executable
 *
 *   1. #include <math.h> only gives the COMPILER a PROTOTYPE:
 *          double sqrt(double);
 *      This tells the compiler "sqrt exists, it takes a double,
 *      it returns a double". It lets compilation succeed.
 *
 *   2. The compiler emits a call to a symbol named "sqrt" in the .o file.
 *      It does NOT contain the body of sqrt().
 *
 *   3. The LINKER must find the actual machine code for "sqrt" in some
 *      library and stitch it into the final executable.
 *
 *   4. On Linux/glibc, sqrt() lives in a SEPARATE library called libm
 *      (the math library: libm.so / libm.a), which is NOT linked by
 *      default. The default link only pulls in libc (and crt startup files).
 *
 *   5. So the linker scans libc, does not find "sqrt", and reports:
 *          undefined reference to `sqrt'
 *
 * WHY SOME FUNCTIONS "JUST WORK"
 * ------------------------------
 *   printf(), malloc(), strlen(), etc. live in libc, which gcc links
 *   automatically. So you never needed -l for those.
 *
 *   sqrt(), pow(), sin(), cos(), tan(), log(), exp(), fabs(), floor(),
 *   ceil(), fmod(), atan2(), hypot(), etc. live in libm and DO need -lm.
 *
 * THE FIX
 * -------
 *   Add -lm to the gcc command:
 *
 *       gcc 2.7_type_conversion.c -o 2.7_type_conversion -lm
 *
 *   Then run:
 *
 *       ./2.7_type_conversion
 *
 * WHAT -lm MEANS
 * --------------
 *   -l<name>  tells the linker: "search the library named lib<name>".
 *   So -lm  =>  search libm  (math library).
 *   Other examples:
 *       -lpthread   -> libpthread   (POSIX threads)
 *       -ldl        -> libdl        (dynamic loading, dlopen)
 *       -lz         -> libz         (zlib compression)
 *       -lreadline  -> libreadline  (GNU readline)
 *
 * ORDER MATTERS (VERY IMPORTANT)
 * ------------------------------
 *   The linker resolves symbols LEFT to RIGHT. A library only satisfies
 *   undefined symbols that appear BEFORE it on the command line.
 *
 *   GOOD (works):
 *       gcc file.c -o out -lm
 *
 *   BAD (still fails):
 *       gcc -lm file.c -o out
 *       gcc file.c -lm -o out        # usually OK, but best at the end
 *
 *   Rule of thumb: put -l<lib> AFTER the source/object files that use it.
 *
 * HOW TO REMEMBER IT FOREVER
 * --------------------------
 *   - #include <math.h>  = "I promise sqrt() exists."  (compiler-side)
 *   - -lm                = "Here, linker, go find sqrt()." (linker-side)
 *   Both are required. One without the other fails.
 *
 * HOW TO INSPECT WHICH LIBRARY A SYMBOL IS IN
 * -------------------------------------------
 *   $ man 3 sqrt
 *       ... shows: "Link with -lm."
 *
 *   $ nm -D /lib/x86_64-linux-gnu/libm.so.6 | grep ' sqrt'
 *       ... shows sqrt is exported by libm.
 *
 *   $ ldd ./2.7_type_conversion
 *       ... shows runtime dependencies (libm.so.6 appears once -lm is used).
 *
 * QUICK REFERENCE
 * ---------------
 *   Compile only (no link):   gcc -c file.c
 *   Compile + link:           gcc file.c -o out
 *   Link with math:           gcc file.c -o out -lm
 *   Recommended with warns:   gcc -Wall -Wextra -std=c99 file.c -o out -lm
 */

int main(void)
{
    // Test atoi_k_and_r
    char num_str[] = "4567";
    int parsed_num = atoi_k_and_r(num_str);
    printf("atoi_k_and_r(\"%s\") = %d\n", num_str, parsed_num);

    // Test lower_ascii_only
    char upper_char = 'K';
    char lower_char = lower_ascii_only(upper_char);
    printf("lower_ascii_only('%c') = '%c'\n", upper_char, lower_char);

    // Test explicit cast with sqrt
    // NOTE: build with -lm, e.g.:
    //   gcc 2.7_type_conversion.c -o 2.7_type_conversion -lm
    int val = 2;
    double root = sqrt((double)val);
    printf("sqrt((double)%d) = %f\n", val, root);

    // Test htoi
    char hex_str[] = "0x1A3F";
    int hex_val = htoi(hex_str);
    printf("htoi(\"%s\") = %d\n", hex_str, hex_val);

    return 0;
}