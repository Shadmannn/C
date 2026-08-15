/*
// 1.THE BINARY ARITHMETIC OPERATORS:

    i.   +   Addition
    ii.  -   Subtraction
    iii. * Multiplication
    iv.  /   Division  (CRITICAL: Integer division TRUNCATES fractional parts!)
    v.   %   Modulus   (Produces the remainder when x is divided by y)

// 2.THE MODULUS OPERATOR (%) CRITICAL RULES:

    - Returns 0 if y divides x exactly (e.g., 4 % 2 == 0).
    - COMPILER RESTRICTION: The % operator CANNOT be applied to 'float' or 'double' types! It only works on integers (char, int, short, long).
    - NEGATIVE OPERANDS BEHAVIOR: For negative numbers, the direction of truncation for / and the algebraic sign of % is machine-dependent.

// 3. LOGICAL LEAP YEAR FORMULA ANALYSIS:

    - A year is a leap year if:
    - Condition A: It is divisible by 4 BUT NOT divisible by 100.
    - OR
    - Condition B: It is divisible by 400 exactly.
    - Code Formula:
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)

// 4. OPERATOR PRECEDENCE & ASSOCIATIVITY

    - HIGHEST:  Unary operators (like unary + and unary - e.g., x = -y)

        *UNARY vs BINARY OPERATORS:
            - Binary: Requires TWO operands (e.g., x + y)
            - Unary:  Requires ONLY ONE operand (e.g., -x, i++, sizeof(int))
            - Rule:   Unary operators are always calculated BEFORE binary operators.

    - MEDIUM:   Multiplicative operators:  * ,  / ,  %
    - LOWEST:   Additive operators:  + ,  -
    - EVALUATION DIRECTION: Arithmetic operators associate Left-to-Right.

 */

#include <stdio.h>

int main() {

// 1. INTEGER DIVISION TRUNCATION MECHANICS:

    printf("--- 1. Integer Division Truncation ---\n");
    int a = 5;
    int b = 2;
    int result_int = a / b;     // Truncates decimal point data completely!
    double result_double = 5.0 / 2.0;

    printf("Integer Division (5 / 2)   = %d <-- Math dropped .5 completely!\n", result_int);
    printf("Floating Division (5.0/2.0) = %.1f\n\n", result_double);


// 2. THE MODULUS (%) OPERATOR:

    printf("--- 2. Modulus (Remainder) Operator ---\n");
    int x = 14;
    int y = 4;

    printf("14 divided by 4 leaves a remainder of: %d\n", x % y);
    printf("Is 12 exactly divisible by 3? Remainder = %d (Yes, 0 means exact!)\n\n", 12 % 3);

    /* COMPILER GUARD NOTE:
     * Un-commenting the line below will crash compilation with an error:
     * "invalid operands to binary %" because floats cannot use modulus!
     *
     * float item = 5.5 % 2.0;
     */

// 3. IMPLEMENTING THE K&R LEAP YEAR ALGORITHM:

    printf("--- 3. Textbook Leap Year Logic Demonstration ---\n");

    // Let's test three target years to prove the logic
    int test_years[3] = {2024, 1900, 2000};

    for(int i = 0; i < 3; i++) {
        int year = test_years[i];

        // Exact expression taken straight out of K&R Figure 2.5
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            printf("-> %d IS a leap year\n", year);
        } else {
            printf("-> %d IS NOT a leap year\n", year);
        }
    }
    printf("\n");


// 4. PRECEDENCE IN ACTION:

    printf("--- 4. Operator Precedence Hierarchy ---\n");

    /* Precedence Rule: '*' and '%' happen BEFORE '+'
     * Math steps:
     * Step 1: 5 * 2 = 10
     * Step 2: 10 % 3 = 1 (Remainder of 10/3)
     * Step 3: 100 + 1 = 101
     */
    int expression = 100 + 5 * 2 % 3;
    printf("Value of (100 + 5 * 2 % 3) = %d\n", expression);

    return 0;
}
