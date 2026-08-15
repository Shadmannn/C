/*

1. DECLARATION:

    - Every variable MUST be declared before it can be used in your code.
    - A declaration tells the compiler two vital things:
        i.  The TYPE of the variable (e.g., int, char, float).
        ii. A LIST of one or more variables belonging to that type.

2. STYLES OF DECLARATION:

    - Grouped Form:  int lower, upper, step;
    - Distributed Form (Preferred):
        int lower;
        int upper;
    - Why distribute? It takes more vertical space, but it lets you write a clear comment next to EACH variable explaining its unique purpose.

3. INITIALIZATION RULES:

    - If you follow a variable name with an equals sign (=) and an expression, that expression acts as an INITIALIZER.
    - AUTOMATIC variables (Local variables created inside a function):
    - Initialized EACH time the function or code block is entered.
    - If NOT explicitly initialized, they contain GARBAGE values (undefined)!
    - Initialized only ONCE, conceptually before the program starts.
    - By default, if you don't initialize them, the compiler sets them to ZERO.

    i)EXTERNAL (GLOBAL) VARIABLES:
        - Both variables are defined OUTSIDE of any function. They are both external variables.
        - By default, external variables are automatically initialized to 0 by the compiler.

            int global_uninitialized;     --- External Variable: Automatically set to 0.
            int global_initialized = 500; --- External Variable: Explicitly initialized to 500.

    ii)STATIC VARIABLES:
        - To make a variable truly "static", you must explicitly use the 'static' keyword.

            static int file_private = 7;  --- Static External Variable: Only visible inside this specific file.

4. THE 'const' QUALIFIER:

    - Can be applied to any variable declaration.
    - It states explicitly that the variable's value WILL NOT BE CHANGED.
    - For Arrays: It means the individual elements cannot be altered.
    - For Function Arguments: Tells the function it is not allowed to modify the original array passed to it (e.g., int strlen(const char[]);).
    - WARNING: Trying to change a const variable results in compile-time errors.

*/

#include <stdio.h>

// External variables (Declared outside functions - Default to 0 if uninitialized)
int global_uninitialized;
int global_initialized = 500;

// Function prototype demonstrating const array protection
int read_only_array_demo(const char message[]);

int main() {

// 1. DISTRIBUTED VS GROUPED DECLARATIONS:

    printf("--- 1. Declaration Styles ---\n");

    // Grouped form
    int lower, upper, step;

    // Distributed form - Allows clean documentation
    char c;             // Holds a single working character
    char line[1000];    // Buffer space to store an input line string

    // Assigning values to show they work perfectly
    lower = 0;
    upper = 300;
    step = 20;
    printf("Values: lower=%d, upper=%d, step=%d\n\n", lower, upper, step);

// 2. INITIALIZATION EXAMPLES FROM THE TEXTBOOK

    printf("--- 2. Initialization ---\n");

    char esc = '\\';          // Initialized with a literal backslash escape sequence
    int i = 0;                // Standard loop index initialization
    #define MAXLINE 1000
    int limit = MAXLINE + 1;  // Initialized using a constant expression calculation
    float eps = 1.0e-5;       // Initialized via scientific notation (0.00001)

    printf("Character literal esc: %c\n", esc);
    printf("Integer i            : %d\n", i);
    printf("Integer limit        : %d\n", limit);
    printf("Float epsilon (eps)  : %f (Scientific: %e)\n\n", eps, eps); // %e = Scientific notation format

// 3. THE GARBAGE VALUE DANGER (Automatic Variables):

    printf("--- 3. Memory Defaults (Global vs Local) ---\n");

    // Automatic variable with NO explicit initializer
    int local_uninitialized;

    printf("Global Uninitialized (External) : %d (Guaranteed 0 by default)\n", global_uninitialized);
    printf("Global Initialized (External)   : %d\n", global_initialized);

    /* WARNING: Reading local_uninitialized right now is dangerous because it
     * contains whatever leftover random data was sitting in your RAM!
     */
    printf("Local Uninitialized (Automatic) : %d <-- DANGER! This is garbage data.\n\n", local_uninitialized);

// 4. THE const QUALIFIER:

    printf("--- 4. Constant Variables (const) ---\n");

    const double e = 2.71828182845905;  // Mathematical Euler constant
    const char msg[] = "warning: ";     // String array that cannot be mutated

    printf("Constant double e  : %.15f\n", e);
    printf("Constant string msg: %s\n", msg);

    /* UNCOMMENTING THE LINES BELOW WILL CAUSE COMPILER TO FAIL (TRY IT!):
     * e = 3.14;         // Error: assignment of read-only variable 'e'
     * msg[0] = 'W';     // Error: assignment of read-only location 'msg[0]'
     */

    printf("\nCalling read_only_array_demo()...\n");
    read_only_array_demo(msg);

    printf("========================================\n");
    return 0;
}

/* Demonstrating function parameter protection with const */
int read_only_array_demo(const char message[]) {
    /*
     * The compiler ensures that 'message' cannot be modified inside here.
     * message[0] = 'X'; <-- This would break the build!
     * Adding 'const' to a function array argument marks it as "READ-ONLY".
     * Trying to alter a const variable causes a compiler crash, catching bugs early!
     */
    printf("Inside function: Safe to read constant data: \"%s\"\n", message);
    return 0;
}
