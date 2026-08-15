#include <stdio.h>
#include <limits.h>
#include <float.h>

/*
 * ============================================================================
 * IMPORTANT: Data type sizes vary by system architecture!
 * 
 * 32-bit systems:
 *   - char:   1 byte  (8 bits)  - ALWAYS 1 byte on ALL systems
 *   - short:  2 bytes (16 bits) - Usually same on 32-bit and 64-bit
 *   - int:    4 bytes (32 bits) - Usually same on 32-bit and 64-bit
 *   - long:   4 bytes (32 bits) - DIFFERS: 4 bytes on 32-bit Windows/Linux
 *   - float:  4 bytes (32 bits) - ALWAYS same across architectures
 *   - double: 8 bytes (64 bits) - ALWAYS same across architectures
 *
 * 64-bit systems (Linux/Unix):
 *   - char:   1 byte  (8 bits)  - ALWAYS 1 byte
 *   - short:  2 bytes (16 bits) - Same as 32-bit
 *   - int:    4 bytes (32 bits) - Same as 32-bit
 *   - long:   8 bytes (64 bits) - DIFFERS: 8 bytes on 64-bit Linux/Unix
 *   - float:  4 bytes (32 bits) - Same as 32-bit
 *   - double: 8 bytes (64 bits) - Same as 32-bit
 *
 * 64-bit systems (Windows - uses LLP64 model):
 *   - long: 4 bytes (32 bits) - Windows keeps long as 4 bytes even on 64-bit!
 *   - All others same as Linux 64-bit
 *
 * This is called the "data model":
 *   - ILP32 (32-bit): int, long, pointer = 32 bits
 *   - LP64 (64-bit Unix/Linux): long, pointer = 64 bits; int = 32 bits
 *   - LLP64 (64-bit Windows): long long, pointer = 64 bits; long, int = 32 bits
 * ============================================================================
 */

/*
 / ** ============================================================================
 * C FORMAT SPECIFIERS LIST
 * ============================================================================
 * SPECIFIER | DATA TYPE USED FOR       | EXAMPLE OUTPUT LOOKS LIKE
 * ----------|--------------------------|--------------------------------------
 * %d or %i | signed integer           | -42, 105   (Base-10 standard int)
 * %u       | unsigned integer         | 4294967295 (Positive integers only)
 * %f       | float / double           | 3.141592   (Standard decimal notation)
 * %e or %E | float / double           | 1.234568e+06 (Scientific notation)
 * %g or %G | float / double           | Uses shorter form of %f or %e automatically
 * %c       | single character (char)  | 'A', '$', '\n'
 * %s       | string (character array) | "hello, world" (Reads up to '\0')
 * %p       | pointer (memory address) | 0x7ffeefbff5ac (Hexadecimal address space)
 * %x or %X | unsigned hexadecimal     | 1a, 2F     (Base-16 shorthand numbers)
 * %o       | unsigned octal           | 54         (Base-8 shorthand numbers)
 * %ld      | long integer             | 2147483648 (Used for wider integers)
 * %lf      | double (for scanf)       | 3.1415926535... (Long float precision)
 * %%       | literal '%' sign         | Prints a single '%' character safely
 * ============================================================================
 * SHAPING OUTPUT MODIFIERS (PRO-TIPS):
 * - %.2f  --> Limits a float to exactly 2 decimal spaces (e.g., 10.50).
 * - %5d   --> Right-aligns an integer inside a visual box 5 spaces wide.
 * - %-5d  --> Left-aligns an integer inside a visual box 5 spaces wide.
 * ============================================================================
*/

void print_separator() {
    printf("\n========================================\n\n");
}

int main() {
    printf("========================================\n");
    printf("   C DATA TYPES AND SIZES\n");
    printf("========================================\n");
    
    /* ========================================================================
     * 1. BASIC DATA TYPES
     * 
     * These 4 types are the foundation of C:
     * - char:   Holds a single character (always 1 byte = 8 bits)
     * - int:    Natural integer size for the machine (usually 4 bytes)
     * - float:  Single-precision floating point (always 4 bytes)
     * - double: Double-precision floating point (always 8 bytes)
     * ========================================================================
     */

    print_separator();
    printf("1. BASIC DATA TYPES\n");
    printf("char:   %zu byte(s)  /* ALWAYS 1 byte on all systems */\n", sizeof(char));
    printf("int:    %zu byte(s)  /* Usually 4 bytes (32 bits) on modern systems */\n", sizeof(int));
    printf("float:  %zu byte(s)  /* ALWAYS 4 bytes - IEEE 754 standard */\n", sizeof(float));
    printf("double: %zu byte(s)  /* ALWAYS 8 bytes - IEEE 754 standard */\n", sizeof(double));
    
    /* ========================================================================
     * 2. INTEGER QUALIFIERS (short, long)
     * 
     * KEY POINT: The word 'int' can be omitted!
     * - "short int" is the same as "short"
     * - "long int" is the same as "long"
     * 
     * ARCHITECTURE DIFFERENCES:
     * - short: ALWAYS 2 bytes (16 bits) on all modern systems
     * - int:   ALWAYS 4 bytes (32 bits) on all modern systems
     * - long:  VARIES!
     *          4 bytes on 32-bit systems
     *          8 bytes on 64-bit Linux/Unix (LP64 model)
     *          4 bytes on 64-bit Windows (LLP64 model)
     * ========================================================================
     */

    print_separator();
    printf("2. INTEGER QUALIFIERS\n");
    printf("short: %zu byte(s)  /* ALWAYS 2 bytes (16 bits) */\n", sizeof(short));
    printf("int:   %zu byte(s)  /* Usually 4 bytes (32 bits) */\n", sizeof(int));
    printf("long:  %zu byte(s)  /* 4 bytes (32-bit) OR 8 bytes (64-bit Linux) */\n", sizeof(long));
    
    /* Demo: 'int' keyword is optional */
    short sh1 = 100;        // Same as 'short int sh1'
    long counter1 = 100000L; // Same as 'long int counter1'
    printf("\n   NOTE: 'short' and 'short int' are identical\n");
    printf("         'long' and 'long int' are identical\n");
    
    /* ========================================================================
     * 3. SIZE RELATIONSHIPS - C STANDARD GUARANTEES
     * 
     * The C standard REQUIRES:
     *   sizeof(short) <= sizeof(int) <= sizeof(long)
     * 
     * This means:
     * - short cannot be larger than int
     * - int cannot be larger than long
     * - They CAN be the same size (e.g., on 32-bit: short=2, int=4, long=4)
     * 
     * PORTABLE CODE: Never assume exact sizes! Use sizeof() or limits.h
     * ========================================================================
     */

    print_separator();
    printf("3. SIZE RELATIONSHIPS (C Standard requires: short <= int <= long)\n");
    printf("   short <= int:  %s (%zu <= %zu)\n", sizeof(short) <= sizeof(int) ? "✓ YES" : "✗ NO", sizeof(short), sizeof(int));
    printf("   int <= long:   %s (%zu <= %zu)\n", sizeof(int) <= sizeof(long) ? "✓ YES" : "✗ NO", sizeof(int), sizeof(long));
    
    printf("\n   EXAMPLE SCENARIOS:\n");
    printf("   32-bit system: short(2) <= int(4) <= long(4)  ✓\n");
    printf("   64-bit Linux:  short(2) <= int(4) <= long(8)  ✓\n");
    printf("   64-bit Windows: short(2) <= int(4) <= long(4) ✓\n");
    
    /* ========================================================================
     * 4. MINIMUM SIZE REQUIREMENTS
     * 
     * C Standard MINIMUM requirements:
     * - short: At least 16 bits (2 bytes)  → can represent -32,768 to 32,767
     * - int:   At least 16 bits (2 bytes)  → can represent -32,768 to 32,767
     * - long:  At least 32 bits (4 bytes)  → can represent -2,147,483,648 to 2,147,483,647
     * 
     * REALITY on modern systems:
     * - short: Exactly 16 bits (2 bytes) on ALL modern systems
     * - int:   Exactly 32 bits (4 bytes) on ALL modern systems
     * - long:  32 bits (32-bit systems) or 64 bits (64-bit Unix/Linux)
     * 
     * WHY? Because compilers choose sizes that match CPU word size for efficiency
     * ========================================================================
     */
    print_separator();
    printf("4. MINIMUM SIZE REQUIREMENTS (from C Standard)\n");
    printf("   short >= 16 bits: %s (%zu bits actual)\n",
           sizeof(short) * 8 >= 16 ? "✓ MET" : "✗ VIOLATED",
           sizeof(short) * 8);
    printf("   int >= 16 bits:   %s (%zu bits actual)\n",
           sizeof(int) * 8 >= 16 ? "✓ MET" : "✗ VIOLATED",
           sizeof(int) * 8);
    printf("   long >= 32 bits:  %s (%zu bits actual)\n",
           sizeof(long) * 8 >= 32 ? "✓ MET" : "✗ VIOLATED",
           sizeof(long) * 8);
    
    printf("\n   PRACTICAL SIZES:\n");
    printf("   Modern 32-bit: short=16, int=32, long=32 bits\n");
    printf("   Modern 64-bit: short=16, int=32, long=64 bits (Unix/Linux)\n");
    printf("                  short=16, int=32, long=32 bits (Windows)\n");
    
    /* ========================================================================
     * 5. SIGNED VS UNSIGNED
     * 
     * CRITICAL CONCEPT: signed vs unsigned changes the RANGE, not the SIZE!
     * 
     * For 8-bit char:
     * - signed char:   -128 to +127        (uses two's complement)
     * - unsigned char:    0 to 255         (all values positive)
     * - plain char:    DEPENDS ON COMPILER! (usually signed, but not guaranteed)
     * 
     * UNSIGNED ARITHMETIC:
     * - Follows "modulo 2^n" arithmetic (where n = number of bits)
     * - unsigned char (8 bits): values wrap at 256 (2^8)
     * - (255 + 1) = 0 (wraps around)
     * - (0 - 1) = 255 (wraps around)
     * 
     * SIGNED OVERFLOW:
     * - Overflow in signed arithmetic is UNDEFINED BEHAVIOR in C!
     * - Unsigned overflow is DEFINED (it wraps)
     * 
     * PORTABILITY WARNING:
     * - Whether plain 'char' is signed or unsigned is IMPLEMENTATION-DEFINED
     * - ALWAYS use 'signed char' or 'unsigned char' if signedness matters
     * - Printable characters (A-Z, a-z, 0-9) are ALWAYS positive
     * ========================================================================
     */
    print_separator();
    printf("5. SIGNED VS UNSIGNED (affects range, not size)\n");
    printf("   signed char:   %d to %d   /* 8 bits, two's complement */\n", 
           SCHAR_MIN, SCHAR_MAX);
    printf("   unsigned char: 0 to %u     /* 8 bits, all positive */\n", 
           UCHAR_MAX);
    printf("   plain char:    %d to %d   /* MACHINE-DEPENDENT! */\n", 
           CHAR_MIN, CHAR_MAX);
    printf("   Is 'char' signed on this system? %s\n", 
           CHAR_MIN < 0 ? "YES (signed)" : "NO (unsigned)");
    
    printf("\n   KEY DIFFERENCES:\n");
    printf("   - signed:   Uses half range for negative, half for positive\n");
    printf("   - unsigned: Uses full range for positive only (0 to 2^n - 1)\n");
    printf("   - unsigned: Wrapping is DEFINED behavior\n");
    printf("   - signed:   Overflow is UNDEFINED behavior!\n");
    
    /* ========================================================================
     * 6. UNSIGNED MODULO ARITHMETIC DEMONSTRATION
     * 
     * MODULO 2^n ARITHMETIC:
     * For unsigned char (8 bits, n=8):
     * - All arithmetic is done "modulo 256" (2^8 = 256)
     * - Maximum value: 255 (2^8 - 1)
     * - 255 + 1 = 256 % 256 = 0 (wraps to minimum)
     * - 0 - 1 = -1 % 256 = 255 (wraps to maximum)
     * 
     * This wrapping is GUARANTEED by the C standard for unsigned types!
     * 
     * PRACTICAL USE CASES:
     * - Checksums and hash functions
     * - Bit manipulation
     * - Circular buffers
     * - Counters that need to wrap (e.g., sequence numbers)
     * ========================================================================
     */
    print_separator();
    printf("6. UNSIGNED MODULO ARITHMETIC (wrapping is DEFINED)\n");
    unsigned char uc = 255;
    printf("   unsigned char = %u (maximum value)\n", uc);
    printf("   255 + 1 = %u  /* Wraps to 0 (modulo 256) */\n", 
           (unsigned char)(uc + 1));
    printf("   255 + 2 = %u  /* Wraps to 1 */\n", 
           (unsigned char)(uc + 2));
    
    uc = 0;
    printf("   0 - 1 = %u    /* Wraps to 255 */\n", 
           (unsigned char)(uc - 1));
    printf("   0 - 2 = %u    /* Wraps to 254 */\n", 
           (unsigned char)(uc - 2));
    
    printf("\n   FORMULA: result = (value) %% (2^n) where n = number of bits\n");
    printf("   For 8-bit unsigned char: result = value %% 256\n");
    
    /* ========================================================================
     * 7. FLOATING-POINT TYPES
     * 
     * CRITICAL: Floating-point sizes are STANDARDIZED (IEEE 754)!
     * 
     * float (32 bits / 4 bytes):
     * - 1 sign bit, 8 exponent bits, 23 mantissa bits
     * - Precision: ~6-7 decimal digits
     * - Range: ±1.2E-38 to ±3.4E+38
     * 
     * double (64 bits / 8 bytes):
     * - 1 sign bit, 11 exponent bits, 52 mantissa bits
     * - Precision: ~15-16 decimal digits
     * - Range: ±2.2E-308 to ±1.8E+308
     * 
     * long double (varies):
     * - 80 bits (10 bytes) on x86 with x87 FPU (Intel extended precision)
     * - 128 bits (16 bytes) on some systems (IEEE 754 quadruple precision)
     * - Sometimes just 64 bits (same as double) on some compilers
     * 
     * UNLIKE INTEGERS: float/double sizes are CONSISTENT across 32/64-bit!
     * 
     * WHY? Because IEEE 754 standard is universally adopted for portability
     * of scientific computations across different systems.
     * ========================================================================
     */
    print_separator();
    printf("7. FLOATING-POINT TYPES (IEEE 754 standard)\n");
    printf("   float:       %zu byte(s), %d decimal digits precision\n", 
           sizeof(float), FLT_DIG);
    printf("                /* 32 bits: 1 sign + 8 exponent + 23 mantissa */\n");
    
    printf("   double:      %zu byte(s), %d decimal digits precision\n", 
           sizeof(double), DBL_DIG);
    printf("                /* 64 bits: 1 sign + 11 exponent + 52 mantissa */\n");
    
    printf("   long double: %zu byte(s), %d decimal digits precision\n", 
           sizeof(long double), LDBL_DIG);
    printf("                /* Varies: 80 bits (x86), 128 bits (some systems) */\n");
    
    printf("\n   PRECISION COMPARISON:\n");
    float f = 3.14159265358979323846f;
    double d = 3.14159265358979323846;
    long double ld = 3.14159265358979323846L;
    
    printf("   float:       %.20f  /* Loses precision after ~7 digits */\n", f);
    printf("   double:      %.20lf  /* Loses precision after ~16 digits */\n", d);
    printf("   long double: %.20Lf\n", ld);
    
    /* ========================================================================
     * 8. COMPLETE INTEGER RANGES
     * 
     * These values come from <limits.h>
     * 
     * WHY THESE SPECIFIC NUMBERS?
     * - signed n-bit: -2^(n-1) to 2^(n-1) - 1 (two's complement)
     * - unsigned n-bit: 0 to 2^n - 1
     * 
     * EXAMPLES:
     * - signed 16-bit: -32,768 to 32,767 (-2^15 to 2^15 - 1)
     * - unsigned 16-bit: 0 to 65,535 (2^16 - 1)
     * - signed 32-bit: -2,147,483,648 to 2,147,483,647 (-2^31 to 2^31 - 1)
     * - unsigned 32-bit: 0 to 4,294,967,295 (2^32 - 1)
     * 
     * PORTABILITY: Use these constants, never hardcode numbers!
     * ========================================================================
     */
    print_separator();
    printf("8. INTEGER RANGES (from <limits.h>)\n");
    
    printf("   CHAR (%zu byte = %zu bits):\n", sizeof(char), sizeof(char) * 8);
    printf("     CHAR_MIN = %d\n", CHAR_MIN);
    printf("     CHAR_MAX = %d\n", CHAR_MAX);
    printf("     /* Plain 'char' is %s on this system */\n", 
           CHAR_MIN < 0 ? "signed" : "unsigned");
    
    printf("\n   SIGNED CHAR (%zu byte = %zu bits):\n", 
           sizeof(signed char), sizeof(signed char) * 8);
    printf("     SCHAR_MIN = %d  /* -2^7 = -128 */\n", SCHAR_MIN);
    printf("     SCHAR_MAX = %d  /* 2^7 - 1 = 127 */\n", SCHAR_MAX);
    
    printf("\n   UNSIGNED CHAR (%zu byte = %zu bits):\n", 
           sizeof(unsigned char), sizeof(unsigned char) * 8);
    printf("     UCHAR_MAX = %u  /* 2^8 - 1 = 255 */\n", UCHAR_MAX);
    
    printf("\n   SHORT (%zu bytes = %zu bits):\n", sizeof(short), sizeof(short) * 8);
    printf("     SHRT_MIN = %d  /* -2^15 = -32,768 */\n", SHRT_MIN);
    printf("     SHRT_MAX = %d  /* 2^15 - 1 = 32,767 */\n", SHRT_MAX);
    printf("     USHRT_MAX = %u  /* 2^16 - 1 = 65,535 */\n", USHRT_MAX);
    
    printf("\n   INT (%zu bytes = %zu bits):\n", sizeof(int), sizeof(int) * 8);
    printf("     INT_MIN = %d  /* -2^31 = -2,147,483,648 */\n", INT_MIN);
    printf("     INT_MAX = %d  /* 2^31 - 1 = 2,147,483,647 */\n", INT_MAX);
    printf("     UINT_MAX = %u  /* 2^32 - 1 = 4,294,967,295 */\n", UINT_MAX);
    
    printf("\n   LONG (%zu bytes = %zu bits):\n", sizeof(long), sizeof(long) * 8);
    printf("     LONG_MIN = %ld\n", LONG_MIN);
    printf("     LONG_MAX = %ld\n", LONG_MAX);
    printf("     ULONG_MAX = %lu\n", ULONG_MAX);
    
    if (sizeof(long) == 4) {
        printf("     /* 32-bit long: -2^31 to 2^31 - 1 */\n");
    } else if (sizeof(long) == 8) {
        printf("     /* 64-bit long: -2^63 to 2^63 - 1 */\n");
    }
    
    /* ========================================================================
     * 9. FLOATING-POINT RANGES
     * 
     * These values come from <float.h>
     * 
     * IMPORTANT CONCEPTS:
     * - MIN: Smallest POSITIVE normalized value (not most negative!)
     * - MAX: Largest finite value
     * - DIG: Number of decimal digits that can be represented exactly
     * - EPSILON: Smallest value where 1.0 + EPSILON != 1.0
     * 
     * DENORMALIZED NUMBERS:
     * - Values smaller than FLT_MIN can exist (denormalized/subnormal)
     * - They have reduced precision
     * - Smallest denormalized float: ~1.4E-45
     * 
     * SPECIAL VALUES:
     * - Infinity: Result of overflow (1.0/0.0)
     * - NaN: Result of invalid operations (0.0/0.0, sqrt(-1))
     * ========================================================================
     */
    print_separator();
    printf("9. FLOATING-POINT RANGES (from <float.h>)\n");
    
    printf("   FLOAT (4 bytes, %d decimal digits):\n", FLT_DIG);
    printf("     FLT_MIN = %e  /* Smallest positive normalized value */\n", FLT_MIN);
    printf("     FLT_MAX = %e  /* Largest finite value */\n", FLT_MAX);
    printf("     FLT_EPSILON = %e  /* Smallest x where 1.0+x != 1.0 */\n", FLT_EPSILON);
    
    printf("\n   DOUBLE (8 bytes, %d decimal digits):\n", DBL_DIG);
    printf("     DBL_MIN = %e\n", DBL_MIN);
    printf("     DBL_MAX = %e\n", DBL_MAX);
    printf("     DBL_EPSILON = %e\n", DBL_EPSILON);
    
    printf("\n   LONG DOUBLE (%zu bytes, %d decimal digits):\n", 
           sizeof(long double), LDBL_DIG);
    printf("     LDBL_MIN = %Le\n", LDBL_MIN);
    printf("     LDBL_MAX = %Le\n", LDBL_MAX);
    printf("     LDBL_EPSILON = %Le\n", LDBL_EPSILON);
    
    /* ========================================================================
     * 10. PRACTICAL ARCHITECTURE SUMMARY
     * 
     * This shows typical sizes on common platforms in 2024:
     * ========================================================================
     */
    print_separator();
    printf("10. YOUR SYSTEM ARCHITECTURE SUMMARY\n");
    printf("    Based on sizeof() results:\n\n");
    
    printf("    Type          | Size (bytes) | Size (bits) | Category\n");
    printf("    --------------|--------------|-------------|------------------\n");
    printf("    char          | %12zu | %11zu | Always 1 byte\n", 
           sizeof(char), sizeof(char) * 8);
    printf("    short         | %12zu | %11zu | Always 2 bytes\n", 
           sizeof(short), sizeof(short) * 8);
    printf("    int           | %12zu | %11zu | Usually 4 bytes\n", 
           sizeof(int), sizeof(int) * 8);
    printf("    long          | %12zu | %11zu | %s\n", 
           sizeof(long), sizeof(long) * 8,
           sizeof(long) == 4 ? "32-bit or Win64" : "64-bit Unix/Linux");
    printf("    float         | %12zu | %11zu | IEEE 754 single\n", 
           sizeof(float), sizeof(float) * 8);
    printf("    double        | %12zu | %11zu | IEEE 754 double\n", 
           sizeof(double), sizeof(double) * 8);
    printf("    long double   | %12zu | %11zu | Extended precision\n", 
           sizeof(long double), sizeof(long double) * 8);
    
    printf("\n    System appears to be: ");
    if (sizeof(long) == 4 && sizeof(void*) == 4) {
        printf("32-bit (ILP32)\n");
    } else if (sizeof(long) == 8 && sizeof(void*) == 8) {
        printf("64-bit Unix/Linux (LP64)\n");
    } else if (sizeof(long) == 4 && sizeof(void*) == 8) {
        printf("64-bit Windows (LLP64)\n");
    } else {
        printf("Unknown/unusual architecture\n");
    }
    
    /* ========================================================================
     * FINAL PORTABILITY ADVICE
     * ========================================================================
     */
    print_separator();
    printf("PORTABILITY BEST PRACTICES:\n\n");
    printf("1. NEVER assume specific sizes - always use sizeof()\n");
    printf("2. Use <limits.h> and <float.h> constants for ranges\n");
    printf("3. For exact-width types, use <stdint.h>:\n");
    printf("   - int8_t, uint8_t   (exactly 8 bits)\n");
    printf("   - int16_t, uint16_t (exactly 16 bits)\n");
    printf("   - int32_t, uint32_t (exactly 32 bits)\n");
    printf("   - int64_t, uint64_t (exactly 64 bits)\n");
    printf("4. For pointer-sized integers, use intptr_t, uintptr_t\n");
    printf("5. For size of objects, use size_t (from <stddef.h>)\n");
    printf("6. Be explicit with signed/unsigned char if signedness matters\n");
    printf("7. Remember: unsigned overflow wraps (defined)\n");
    printf("              signed overflow is undefined behavior!\n");
    
    print_separator();
    
    return 0;
}
