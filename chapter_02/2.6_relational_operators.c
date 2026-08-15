/*
 // 1. THE RELATIONAL AND EQUALITY OPERATORS:

 * Relational Operators:  >   >=   <   <=  (All share equal precedence)
 * Equality Operators:    ==  !=           (Equal precedence, but LOWER than relational)

 // 2. CORE PRECEDENCE HIERARCHY RULE:

 - Arithmetic operators (+, -, *, /, %) have HIGHER precedence than relational operators.
 - Therefore, an expression like: i < lim - 1   is automatically evaluated as   i < (lim - 1)

 // 3. LOGICAL OPERATORS & SHORT-CIRCUIT EVALUATION:

 - &&  Logical AND (Both conditions must be true)
 - ||  Logical OR  (At least one condition must be true)

 - CRITICAL PERFORMANCE RULE: Left-to-Right "Short-Circuit" Evaluation
 - Evaluation STOPS completely the split-second the truth or falsehood of the overall expression is finalized!
 - For &&: If the left side is FALSE, the right side is NEVER evaluated.
 - For ||: If the left side is TRUE, the right side is NEVER evaluated.

 // 4. NUMERIC TRUTH VALUES AND UNARY NEGATION (!):

 - True/False Numbers: In C, a true relation evaluates to 1; false evaluates to 0.
 - Unary Negation (!): Converts a non-zero (true) value into 0, and a zero (false) value into 1.
 - Idiomatic Form: 'if (!valid)' reads cleaner than 'if (valid == 0)'.
*/

#include <stdio.h>

int main() {

    // 1. ARITHMETIC VS RELATIONAL PRECEDENCE:
    printf("--- 1. Precedence: Arithmetic vs Relational ---\n");
    int i = 5;
    int limit = 10;

    // K&R Example: 'limit - 1' is calculated FIRST before comparing to 'i'
    if (i < limit - 1) { // Evaluates as: i < (10 - 1) -> 5 < 9 which is TRUE
        printf("Expression (i < lim - 1) is TRUE\n\n");
    }

    // 2. THE NUMERIC VALUE OF TRUTH IN C:
    printf("--- 2. Numeric Values of True and False ---\n");
    int true_outcome = (10 > 2);  // Mathematically true
    int false_outcome = (10 < 2); // Mathematically false

    printf("Value of a TRUE expression (10 > 2)   : %d\n", true_outcome);
    printf("Value of a FALSE expression (10 < 2)  : %d\n\n", false_outcome);


    /* ------------------------------------------------------------------------
     * 3. THE SHORT-CIRCUIT SAFETY GUARANTEE DEMONSTRATION
     * ------------------------------------------------------------------------
     */
    printf("--- 3. Short-Circuit Evaluation Safeguard ---\n");

    int array[5] = {10, 20, 30, 40, 50};
    int max_limit = 5;

    // Test Case A: Index is safely within bounds
    int index_safe = 2;
    printf("Testing Safe Index (2):\n");
    if (index_safe < max_limit && array[index_safe] == 30) {
        printf("-> Success: Element matches 30 safely.\n");
    }

    // Test Case B: Index is dangerous (Out of Bounds!)
    int index_danger = 99;
    printf("Testing Dangerous Index (99):\n");

    /* WHY THIS DOES NOT CRASH YOUR PROGRAM:
     * Step 1: Evaluates (index_danger < max_limit) -> (99 < 5), which is FALSE.
     * Step 2: Because it's an '&&' operator, the overall statement is already guaranteed false.
     * Step 3: C SHORT-CIRCUITS! It bypasses reading 'array[99]' completely.
     * If C didn't short-circuit, reading array[99] would cause a segmentation fault crash!
     */
    if (index_danger < max_limit && array[index_danger] == 999) {
        // This block will never run
    } else {
        printf("-> Protected! Short-circuit stopped evaluation before accessing array[999]!\n\n");
    }


    /* ------------------------------------------------------------------------
     * 4. THE K&R getline() LOOP COMPLEX PRECEDENCE DECONSTRUCTION
     * ------------------------------------------------------------------------
     */
    printf("--- 4. Deconstructing the K&R Loop Syntax ---\n");
    printf("Textbook complex loop layout expression:\n");
    printf("for (i=0; i < lim-1 && (c = getchar()) != '\\n' && c != EOF; ++i)\n\n");

    /* Let's analyze why parentheses matter here based on K&R text:
     * 1. '!=' has higher precedence than '=' (assignment).
     * 2. If we wrote: c = getchar() != '\n'
     * The computer would evaluate (getchar() != '\n') first, giving a 1 (True) or 0 (False).
     * Then it would assign that 1 or 0 to 'c', completely wiping out your actual text character!
     * 3. Parentheses around '(c = getchar())' force C to store the letter inside 'c' FIRST,
     * and then test it against '\n'.
     */
    printf("Parentheses force character storage before matching conditions!\n\n");


    /* ------------------------------------------------------------------------
     * 5. UNARY NEGATION OPERATOR (!)
     * ------------------------------------------------------------------------
     */
    printf("--- 5. Unary Negation (!) Clean Code Form ---\n");
    int valid = 0; // 0 means false

    if (!valid) { // Reads as: "If NOT valid"
        printf("Condition matched: '!valid' successfully turned 0 into %d (True)!\n\n", !valid);
    }

    printf("==================================================\n");

    /* ============================================================================
     * EXERCISE 2.2 SOLUTION: Loop without && or ||
     * ============================================================================
     */
    printf("--- 6. Exercise 2.2 Interactive Demonstration ---\n");
    printf("Type a sentence and press ENTER: ");

    // DECLARATIONS NEEDED FOR EXERCISE 2.2:
    char s[1000]; // 1000-box buffer to store the user's string
    int c;        // Variable to hold each character read from keyboard
    int i = 0;  // Loop index counter
    int ok = 1;   // Logic flag: 1 means continue, 0 means stop
    limit = 1000;   // Buffer size limit

    while (ok) {
        if (i >= limit - 1) {
            ok = 0; // Stop! No more room in array s[]
        } else if ((c = getchar()) == '\n') {
            ok = 0; // Stop! User pressed Enter
        } else if (c == EOF) {
            ok = 0; // Stop! Reached End-of-File
        } else {
            s[i] = c; // Safe to store character
            ++i;
        }
    }

    s[i] = '\0'; // Add null terminator to complete string

    printf("Result saved in s[]: \"%s\"\n", s);
    printf("==================================================\n");

    return 0;
}
