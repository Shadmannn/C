/*
 * General Overview:
 * C provides two unary operators for incrementing and decrementing
 * variables:
 *   - '++' adds 1 to its operand.
 *   - '--' subtracts 1 from its operand.
 *
 * x = a + 5;  -- x, a, and 5 are operands; '+' and '=' are operators.
 *
 * Key Characteristic:
 *
 * Both operators can be used either as PREFIX operators (++n, --n) or
 * POSTFIX operators (n++, n--).
 *
 * In both cases, 'n' is updated (incremented or decremented) in memory.
 * However, in expressions where the value of the operation is evaluated:
 *   - Prefix (++n)  : Increments 'n' BEFORE its value is fetched for use.
 *   - Postfix (n++) : Fetches 'n's CURRENT value for use, then increments 'n'.
 */

/*
 * 1. lvalue ("Locator Value")
 *
 * An lvalue refers to an object that occupies an identifiable, persistent
 * location in memory (RAM, Stack, or Data Segment).
 *
 * Core Properties:
 *   - Has a persistent memory address (the address-of operator '&lvalue'
 *     is valid).
 *   - Lifetime persists beyond the single executing expression.
 *   - Can appear on the LEFT side of an assignment '=' (if non-const
 *     modifiable).
 *
 * Examples of lvalues:
 *   int x = 10;        -- 'x' is an lvalue (persistent stack memory address).
 *   int arr[5];        -- 'arr[0]' is an lvalue.
 *   struct Point p;    -- 'p.x' is an lvalue.
 *   int *ptr = &x;     -- '*ptr' (dereferenced pointer) is an lvalue.
 */

/*
 * 2. rvalue ("Read Value" or "Right Value")
 *
 * An rvalue is a temporary data value that does NOT have a persistent,
 * identifiable memory address. It lives temporarily inside a CPU register
 * or is encoded into intermediate instruction stream machine code.
 *
 * Core Properties:
 *   - Does NOT have an accessible memory address ('&rvalue' is a compiler
 *     error).
 *   - Temporary lifetime (vanishes once the current expression finishes
 *     executing).
 *   - CANNOT appear on the left side of an assignment operator '='.
 *
 * Examples of Rvalues:
 *   10                 -- Literal constant (embedded in CPU opcode byte stream).
 *   x + 5              -- Intermediate result calculated into ALU CPU register.
 *   sqrt(4.0)          -- Temporary function return value before storage.
 */

/*
 * WHY ++ AND -- REQUIRE AN LVALUE
 *
 * In C, expressions like '5++' or '(i + j)++' fail to compile with errors
 * like:
 *   "error: lvalue required as increment operand"
 *
 * Code Example:
 *   int i = 2, j = 3;
 *   i++;       -- LEGAL: 'i' is an lvalue (a variable in memory).
 *   (i + j)++; -- ILLEGAL: '(i + j)' produces an rvalue.
 *
 * Low-Level CPU Explanation:
 *   1. The expression '(i + j)' is evaluated by loading 'i' and 'j' into
 *      CPU registers and running an arithmetic ADD instruction.
 *   2. The result (5) exists solely inside a CPU register (e.g., EAX) as
 *      an RVALUE.
 *   3. The '++' operator must fetch a value from memory, increment it, and
 *      WRITE THE NEW VALUE BACK TO THAT MEMORY LOCATION.
 *   4. Because a temporary CPU register computation has no memory address
 *      in RAM, there is no place for the CPU to store the incremented
 *      result back to!
 */

#include <stdio.h>

/*
 * 1. PREFIX VS. POSTFIX MECHANICS & LVALUE RESTRICTION
 *
 * Difference in Action:
 *   If n = 5:
 *     x = n++;   -- x gets 5, then n becomes 6 (Postfix: fetch value,
 *                   then mutate)
 *     x = ++n;   -- n becomes 6, then x gets 6 (Prefix: mutate, then
 *                   fetch value)
 *
 * Context Matters:
 *   When used as a standalone statement where the expression result is
 *   discarded, prefix and postfix are functionally identical:
 *     nl++;   <-- Equivalent to -->   ++nl;
 *
 * LVALUE RESTRICTION:
 *   ++ and -- can ONLY be applied to MODIFIABLE LVALUES (variables or
 *   memory locations). They CANNOT be applied to rvalue expressions or
 *   literal values.
 *
 *   Illegal Examples:
 *     (i + j)++   -- ERROR: (i + j) produces a temporary rvalue result,
 *                    not a memory location.
 *     5++         -- ERROR: 5 is a constant literal, not a variable.
 */

void demonstrate_prefix_vs_postfix(void)
{
	int n = 5;
	int x;

	/* Postfix: x gets the old value of n */
	x = n++;
	printf("Postfix (x = n++): x = %d, n = %d\n", x, n);

	n = 5;	/* reset */

	/* Prefix: x gets the new value of n */
	x = ++n;
	printf("Prefix  (x = ++n): x = %d, n = %d\n", x, n);
}

/*
 * 2. COMPACT POINTER/INDEXING PATTERNS
 *
 * Postfix incrementing allows C programmers to write concise buffer
 * manipulation loops where an array index is consumed and advanced in a
 * single step.
 */

/*
 * Example 1: squeeze_k_and_r(s, c)
 * Removes all occurrences of character 'c' from string 's'.
 *
 * Idiom Analysis:
 *   s[j++] = s[i];
 *
 * Micro-step execution order:
 *   1. Fetch value of 'j' (e.g., 0).
 *   2. Copy character s[i] into destination address s[j].
 *   3. Increment 'j' by 1 so it points to the next available slot for
 *      future writes.
 */
void squeeze_k_and_r(char s[], int c)
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++) {
		if (s[i] != c) {
			/* Write char to s[j], then increment j */
			s[j++] = s[i];
		}
	}
	/* Null-terminate squeezed string at the updated write head */
	s[j] = '\0';
}

/*
 * Example 2: strcat_k_and_r(s, t)
 * Concatenates string 't' onto the end of string 's'.
 * 's' must be sized with sufficient capacity to hold both strings.
 */
void strcat_k_and_r(char s[], char t[])
{
	int i, j;

	i = j = 0;
	/* Step 1: Advance 'i' until reaching the end of destination 's' */
	while (s[i] != '\0') {
		i++;
	}

	/*
	 * Step 2: Copy 't' to the tail of 's', advancing both indices
	 * simultaneously.
	 */
	while ((s[i++] = t[j++]) != '\0') {
		/*
		 * Null body; copy and increment happen inside the
		 * condition test.
		 */
		;
	}
}

/*
 * 3. UNDEFINED BEHAVIOR (UB): INCREMENT OPERATORS & SEQUENCE POINTS
 *
 * CRITICAL C RULE:
 * C does NOT guarantee left-to-right evaluation for most expressions.
 * Modifying a variable and reading/modifying it again in a single
 * statement without an intervening sequence point causes UNDEFINED
 * BEHAVIOR (UB).
 *
 * EXAMPLE OF BROKEN CODE:
 *   a[i] = i++;
 *
 * WHAT GOES WRONG AT THE HARDWARE LEVEL:
 * The CPU must perform three distinct steps:
 *   1. Resolve the array index `a[i]`.
 *   2. Read the value of `i` to place inside the array.
 *   3. Increment `i` in memory/register.
 *
 * Because C does not dictate the evaluation order, different compilers
 * or optimization levels (-O0 vs -O3) can execute these in different
 * orders:
 *   - Order A: Resolves `a[0]` first -> stores 0 in `a[0]`, then `i`
 *              becomes 1.
 *   - Order B: Increments `i` to 1 first -> resolves `a[1]`, stores 0
 *              in `a[1]`.
 *
 * OTHER DANGEROUS PATTERNS:
 *   int x = i++ + i;            -- Unspecified order around '+'
 *   printf("%d %d", n++, n++);  -- Unspecified argument evaluation order
 *
 * THE FIX:
 * Separate side-effects using a semicolon `;` (which creates a
 * sequence point):
 *   a[i] = i;  -- Step 1: Assign value first
 *   i++;       -- Step 2: Increment index
 */

/*
 * 4. K&R EXERCISE 2-4 SOLUTION
 *
 * Exercise 2-4: Write an alternative version of squeeze(s1, s2) that
 * deletes each character in s1 that matches ANY character in the string
 * s2.
 *
 * Algorithm Complexity: O(N * M) where N = strlen(s1), M = strlen(s2).
 */

/* Helper function to check if character 'c' exists in string 's2' */
static int contains_char(const char s2[], char c)
{
	int k;

	for (k = 0; s2[k] != '\0'; k++) {
		if (s2[k] == c) {
			/* Character found */
			return 1;
		}
	}
	/* Character not present */
	return 0;
}

void squeeze_multi(char s1[], const char s2[])
{
	int i, j;

	for (i = j = 0; s1[i] != '\0'; i++) {
		/* If current char s1[i] is NOT in s2, keep it */
		if (!contains_char(s2, s1[i])) {
			/* Write and advance destination pointer */
			s1[j++] = s1[i];
		}
	}
	/* Null terminate */
	s1[j] = '\0';
}

/*
 * 5. K&R EXERCISE 2-5 SOLUTION
 * 
 * Exercise 2-5: Write the function any(s1, s2), which returns the FIRST
 * location in a string s1 where ANY character from string s2 occurs, or
 * -1 if s1 contains no characters from s2.
 *
 * Note: Matches the behavior of standard C library function strpbrk(),
 * except strpbrk() returns a pointer to the location rather than an
 * integer index.
 */
int any(const char s1[], const char s2[])
{
	int i, k;

	for (i = 0; s1[i] != '\0'; i++) {
		for (k = 0; s2[k] != '\0'; k++) {
			if (s1[i] == s2[k]) {
				/* Return immediate first matching index in s1 */
				return i;
			}
		}
	}

	/* No matching characters found */
	return -1;
}


/* 6. DRIVER / TEST HARNESS */
int main(void)
{
	printf("--- 1. PREFIX VS POSTFIX DEMONSTRATION ---\n");
	demonstrate_prefix_vs_postfix();

	printf("\n--- 2. K&R SQUEEZE DEMO ---\n");
	char str_squeeze[] = "embedded_systems";
	printf("Original: %s\n", str_squeeze);
	squeeze_k_and_r(str_squeeze, 'e');
	printf("After squeeze('e'): %s\n", str_squeeze);

	printf("\n--- 3. K&R STRCAT DEMO ---\n");
	char dest[50] = "Kernel_";
	char src[] = "Development";
	strcat_k_and_r(dest, src);
	printf("After strcat: %s\n", dest);

	printf("\n--- 4. EXERCISE 2-4: squeeze_multi(s1, s2) ---\n");
	char s1[] = "the quick brown fox jumps over the lazy dog";
	char s2[] = "aeiou"; /* Strip all vowels */
	printf("Before squeeze_multi: \"%s\"\n", s1);
	squeeze_multi(s1, s2);
	printf("After stripping \"%s\": \"%s\"\n", s2, s1);

	printf("\n--- 5. EXERCISE 2-5: any(s1, s2) ---\n");
	char haystack[] = "linux_kernel";
	char needle_found[] = "xyz_k";
	char needle_absent[] = "abc";

	int idx1 = any(haystack, needle_found);
	int idx2 = any(haystack, needle_absent);

	printf("any(\"%s\", \"%s\") = %d (Expected: matching index)\n",
	       haystack, needle_found, idx1);
	printf("any(\"%s\", \"%s\") = %d (Expected: -1)\n",
	       haystack, needle_absent, idx2);

	return 0;
}